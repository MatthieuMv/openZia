/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** APipeline template sources
*/

#include <cstring>

#include "APipeline.hpp"

using namespace oZ;

void APipeline::loadModules(const std::string &directoryPath)
{
    for (auto &state : _pipeline)
        state.clear();
    _modules.clear();
    onLoadModules(directoryPath);
    checkModulesDependencies();
    createPipeline();
}

void APipeline::runPipeline(Context &&context)
{
    while (!context.hasError() && !context.isCompleted()) {
        triggerContextStateCallbacks(context);
        context.nextState();
    }
    if (context.hasError())
        triggerContextStateCallbacks(context);
}

void APipeline::triggerContextStateCallbacks(Context &context)
{
    for (const auto &callback : _pipeline[context.getState()]) {
        callback.second(context);
    }
}

void APipeline::checkModulesDependencies(void)
{
    for (const auto &module : _modules) {
        for (const auto *dependencie : module->getDependencies())
            checkModuleDependency(module, dependencie);
    }
}

void APipeline::checkModuleDependency(const ModulePtr &module, const char *dependency)
{
    auto it = std::find_if(_modules.begin(), _modules.end(),
                [dependency](const auto &m) { return !std::strcmp(m->getName(), dependency); });
    
    if (it == _modules.end())
        throw std::logic_error(std::string("Pipeline::checkModuleDependencies: ") + module->getName() + "' requires missing module '" + dependency + '\'');
}

void APipeline::createPipeline(void)
{
    const auto handler = std::bind(&APipeline::onRegister, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (const auto &module : _modules) {
        module->registerCallbacks(handler);
    }
}

void APipeline::onRegister(State state, Priority priority, CallbackHandler &&handler)
{
    auto &callbacks = _pipeline[state];
    auto it = callbacks.cbegin();

    while (it != callbacks.end() && it->first < priority)
        ++it;
    callbacks.insert(it, std::make_pair(priority, std::move(handler)));
}
