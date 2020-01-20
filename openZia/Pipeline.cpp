/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline template sources
*/

#include <cstring>

#include "Pipeline.hpp"

using namespace oZ;

Pipeline::Pipeline(std::string &&moduleDir, std::string &&configurationDir)
    : _moduleDir(std::move(moduleDir)), _configurationDir(std::move(configurationDir))
{
    loadModules();
}

void Pipeline::loadModules(void)
{
    for (auto &state : _pipeline)
        state.clear();
    _modules.clear();
    onLoadModules(_moduleDir);
    checkModulesDependencies();
    createPipeline();
}

void Pipeline::onLoadModules(const std::string &directoryPath)
{
    (void)(directoryPath);
}


void Pipeline::registerCallback(State state, Priority priority, CallbackHandler &&handler)
{
    auto &callbacks = _pipeline[state];
    auto it = callbacks.cbegin();

    while (it != callbacks.end() && it->first > priority)
        ++it;
    callbacks.insert(it, std::make_pair(priority, std::move(handler)));
}

void Pipeline::runPipeline(Context &context)
{
    do {
        triggerContextStateCallbacks(context);
    } while (context.nextState());
    if (context.hasError())
        triggerContextStateCallbacks(context);
}

void Pipeline::triggerContextStateCallbacks(Context &context)
{
    for (const auto &callback : _pipeline[context.getState()]) {
        if (!callback.second(context))
            break;
    }
}

void Pipeline::checkModulesDependencies(void)
{
    for (const auto &module : _modules) {
        for (const auto *dependencie : module->getDependencies())
            checkModuleDependency(module, dependencie);
    }
}

void Pipeline::checkModuleDependency(const ModulePtr &module, const char *dependency)
{
    auto it = std::find_if(_modules.begin(), _modules.end(),
                [dependency](const auto &m) { return !std::strcmp(m->getName(), dependency); });

    if (it == _modules.end())
        throw std::logic_error(std::string("Pipeline::checkModuleDependencies: ") + module->getName() + "' requires missing module '" + dependency + '\'');
}

void Pipeline::createPipeline(void)
{
    for (const auto &module : _modules) {
        module->onRegisterCallbacks(*this);
        module->onRetreiveDependencies(*this);
        module->onLoadConfigurationFile(_configurationDir);
    }
}
