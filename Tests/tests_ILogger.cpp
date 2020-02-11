/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module Interface
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <iostream>

#include <openZia/Log.hpp>
#include <openZia/Pipeline.hpp>

using namespace oZ;

class BasicLogger : public ILogger
{
public:
    virtual ~BasicLogger(void) = default;

    virtual void onLog(Level, const std::string &str) { std::cout << str << std::endl; }

    virtual const char *getName(void) const { return "BasicLogger"; }
};

class MyPipeline : public Pipeline
{
public:
    virtual void onLoadModules(const std::string &) override { addModule<BasicLogger>(); }
};

Test(ILogger, Basics, .init=cr_redirect_stdout)
{
    MyPipeline pipeline;

    pipeline.loadModules();
    oZ::Log() << "Hello";
    cr_assert_stdout_eq_str("Hello\n");
}