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
#include "Log.hpp"

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

void Pipeline::onConnection(const FileDescriptor fd, const Endpoint endpoint, const bool useEncryption)
{
    for (auto &module : _modules)
        module->onConnection(fd, endpoint, useEncryption);
}

void Pipeline::onDisconnection(const FileDescriptor fd, const Endpoint endpoint)
{
    for (auto &module : _modules)
        module->onDisconnection(fd, endpoint);
}

void Pipeline::onLoadModules(const std::string &directoryPath)
{
    fs::path path(directoryPath);

    if (!fs::exists(path))
        throw std::logic_error("Pipeline::onLoadModules: Inexisting module directory '" + directoryPath + '\'');
    for (const auto &file : fs::directory_iterator(path)) {
        if (!file.path().has_extension())
            continue;
        else if (auto ext = file.path().extension().string(); ext != std::string(SHARED_LIB_EXT))
            continue;
        auto handler = _dynamicLoader.load(file.path().string());
        auto function = _dynamicLoader.getFunction<ModuleInstanceFunction>(handler, OPEN_ZIA_ENTRY_POINT_AS_STRING);
        addModule(ModulePtr((*function)()));
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

void Pipeline::addModule(ModulePtr &&module)
{
    if (auto log = std::dynamic_pointer_cast<ILogger>(module); log)
        Log::AddLogger(log);
    _modules.emplace_back(std::move(module));
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
