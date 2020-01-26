/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline Abstraction
*/

#include <criterion/criterion.h>

#include <openZia/Pipeline.hpp>

#include "Utils.hpp"

using namespace oZ;

Test(Pipeline, Basics)
{
    Pipeline pipeline(".", ".");

    pipeline.loadModules();
    cr_assert_eq(pipeline.getModules().size(), 1);
    cr_assert_not(pipeline.findModule("aze"));
    cr_assert(pipeline.findModule("Foo"));
}

Test(Pipeline, InexistingModuleDir)
{
    cr_assert(CrashTest([] { Pipeline("azerty").loadModules(); }));
}

/*
  Test hierarchy
0:    A
1:   B C
*/

class B;
class C;

class A : public IModule
{
public:
    virtual const char *getName(void) const { return "A"; }

    virtual void onRegisterCallbacks(Pipeline &pipeline) {
        pipeline.registerCallback(State::Parse, Priority::Independent, this, &A::foo);
        registered = true;
    }

    virtual void onRetreiveDependencies(Pipeline &pipeline) {
        b = pipeline.findModule<B>();
        c = pipeline.findModule<C>();
    }

    virtual void onLoadConfigurationFile(const std::string &) { configured = true; }

    virtual Dependencies getDependencies(void) const noexcept { return { "B", "C" }; }

    bool foo(Context &) { ++x; return true; }

    int x = 0;
    bool registered = false, configured = false;
    std::shared_ptr<B> b;
    std::shared_ptr<C> c;
};

class B : public IModule
{
public:
    virtual const char *getName(void) const { return "B"; }

    virtual void onRegisterCallbacks(Pipeline &pipeline) {
        pipeline.registerCallback(State::Interpret, Priority::ASAP, [this](Context &) { ++x; return false; });
        pipeline.registerCallback(State::AfterInterpret, Priority::Independent, [this](Context &ctx) { ctx.setErrorState(); return false; });
    }

    int x = 0;
};

class C : public IModule
{
public:
    virtual const char *getName(void) const { return "C"; }

    virtual void onRegisterCallbacks(Pipeline &pipeline) {
        pipeline.registerCallback(State::Parse, Priority::Independent, [this](Context &) { ++x; return true; });
        pipeline.registerCallback(State::Interpret, Priority::Independent, [this](Context &) { ++x; return true; });
    }

    int x = 0;
};

class ABCPipeline : public Pipeline
{
public:
    virtual void onLoadModules(const std::string &) override {
        addModule<A>();
        addModule<B>();
        addModule<C>();
    }
};

Test(Pipeline, ABC)
{
    ABCPipeline pipeline;
    Context ctx;

    pipeline.loadModules();
    auto a = pipeline.findModule<A>();
    cr_assert(a);
    cr_assert(a->registered);
    cr_assert(a->configured);
    cr_assert(a->b);
    cr_assert(a->c);
    pipeline.runPipeline(ctx);
    cr_assert_eq(ctx.getState(), State::Error);
    cr_assert_eq(a->x, 1);
    cr_assert_eq(a->b->x, 1);
    cr_assert_eq(a->c->x, 1);
}


class Abis : public A
{
public:
    virtual Dependencies getDependencies(void) const noexcept { return { "B", "E" }; }
};

class AbisPipeline : public Pipeline
{
    virtual void onLoadModules(const std::string &) override {
        addModule<Abis>();
        addModule<B>();
    }
};

Test(Pipeline, Abis)
{
    AbisPipeline pipeline;
    Context ctx;

    cr_assert(CrashTest([&pipeline] { pipeline.loadModules(); }));
    cr_assert_not(pipeline.findModule<C>());
}