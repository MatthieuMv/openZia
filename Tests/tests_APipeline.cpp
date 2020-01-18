/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline Abstraction 
*/

#include <criterion/criterion.h>

#include <openZia/APipeline.hpp>

using namespace oZ;

class Pipeline : public APipeline
{
    virtual void onLoadModules(const std::string &) {}
};

Test(APipeline, Basics)
{
    Pipeline pipeline;

    cr_assert(pipeline.getModules().empty());
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

    virtual void onRegisterCallbacks(APipeline &pipeline) {
        pipeline.registerCallback(State::Analyze, Priority::Independent, this, &A::foo);
        registered = true;
    }

    virtual void onRetreiveDependencies(APipeline &pipeline) {
        b = pipeline.findModule<B>();
        c = pipeline.findModule<C>();
    }

    virtual void onLoadConfigurationFile(const std::string &) { configured = true; }

    virtual Dependencies getDependencies(void) const noexcept { return { "B", "C" }; }

    void foo(Context &) { ++x; }

    int x = 0;
    bool registered = false, configured = false;
    std::shared_ptr<B> b;
    std::shared_ptr<C> c;
};

class B : public IModule
{
public:
    virtual const char *getName(void) const { return "B"; }

    virtual void onRegisterCallbacks(APipeline &pipeline) {
        pipeline.registerCallback(State::Parse, Priority::Independent, [this](Context &) { ++x; });
    }
    
    int x = 0;
};

class C : public IModule
{
public:
    virtual const char *getName(void) const { return "C"; }

    virtual void onRegisterCallbacks(APipeline &pipeline) {
        pipeline.registerCallback(State::Response, Priority::Independent, [this](Context &) { ++x; });
    }
    
    int x = 0;
};

class ABCPipeline : public APipeline
{
    virtual void onLoadModules(const std::string &) {
        addModule<A>();
        addModule<B>();
        addModule<C>();
    }
};

Test(APipeline, ABC)
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
    cr_assert_eq(a->x, 1);
    cr_assert_eq(a->b->x, 1);
    cr_assert_eq(a->c->x, 1);
}