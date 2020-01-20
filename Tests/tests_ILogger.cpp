/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module Interface
*/

#include <criterion/criterion.h>

#include <openZia/ILogger.hpp>
#include <openZia/Pipeline.hpp>

using namespace oZ;

class MyPipeline : public Pipeline
{
    virtual void onLoadModules(const std::string &) {}
};

class BasicLogger : public ILogger
{
public:
    virtual ~BasicLogger(void) = default;

    virtual void onLog(Level, const std::string &) {}

    virtual const char *getName(void) const { return "BasicLogger"; }
};

Test(ILogger, Basics)
{
    MyPipeline pipeline;
    BasicLogger logger;

    logger.onRegisterCallbacks(pipeline);
}