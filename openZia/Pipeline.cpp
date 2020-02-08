/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline template sources
*/

#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #error "You compiler doesn't support std::filesystem nor std::experimental::filesystem"
#endif

#include <cstring>

#include "Pipeline.hpp"

using namespace std::string_literals;
using namespace oZ;

Pipeline::Pipeline(std::string &&moduleDir, std::string &&configurationDir)
    : _moduleDir(std::move(moduleDir)), _configurationDir(std::move(configurationDir))
{
}

void Pipeline::loadModules(void)
{
    for (auto &state : _pipeline)
        state.clear();
    _modules.clear();
    _dynamicLoader.release();
    onLoadModules(_moduleDir);
    checkModulesDependencies();
    createPipeline();
}

ModulePtr Pipeline::findModule(const char *name) const
{
    for (const auto &module : _modules) {
        if (!std::strcmp(module->getName(), name))
            return module;
    }
    return nullptr;
}

void Pipeline::onLoadModules(const std::string &directoryPath)
{
    fs::path path(directoryPath);

    if (!fs::exists(path))
        throw std::logic_error("Pipeline::onLoadModules: Inexisting module directory '" + directoryPath + '\'');
    for (const auto &file : fs::directory_iterator(path)) {
        if (!file.path().has_extension())
            continue;
        else if (auto ext = file.path().extension().string(); ext != ".dll" && ext != ".so")
            continue;
        auto handler = _dynamicLoader.load(file.path().string());
        auto function = _dynamicLoader.getFunction<ModuleInstanceFunction>(handler, "CreateModule");
        _modules.emplace_back((*function)());
    }
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
    if (!std::any_of(_modules.begin(), _modules.end(),
            [dependency](const auto &m) { return !std::strcmp(m->getName(), dependency); }))
        throw std::logic_error("Pipeline::checkModuleDependencies: "s + module->getName() + "' requires missing module '" + dependency + '\'');
}

void Pipeline::createPipeline(void)
{
    if (!_configurationDir.empty() && _configurationDir.back() != '/')
        _configurationDir.push_back('/');
    for (const auto &module : _modules) {
        module->onRegisterCallbacks(*this);
        module->onRetreiveDependencies(*this);
        module->onLoadConfigurationFile(_configurationDir);
    }
}
