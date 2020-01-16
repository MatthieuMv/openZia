/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline abstraction
*/

#pragma once

#include <string>
#include <functional>

#include "ILogger.hpp"

namespace oZ
{
    class APipeline;
}

/**
 * @brief The pileline abstracts the pipeline of modules.
 */
class oZ::APipeline
{
public:
    /**
     * @brief Simple vector of modules
     */
    using ModuleList = std::vector<ModulePtr>;

    /**
     * @brief Array containing a vector of callback fo each state
     */
    using PipelineMap = std::array<std::vector<std::pair<Priority, CallbackHandler>>, State::StateCount>;

    /**
     * @brief Vector containing ILogger modules
     */
    using LoggerList = std::vector<LoggerPtr>;

    /**
     * @brief Construct a new Pipeline object
     */
    APipeline(void) = default;

    /**
     * @brief Destroy the Pipeline object
     */
    virtual ~APipeline(void) = default;

    /**
     * @brief Find modules and load them into the pipeline.
     *  This function will :
     *      1) Trigger the onLoadModules callback that you should implement yourself
     *      2) Check if modules dependencies are avaible
     *      3) Build the internal pipeline with it.
     *      4) Load configuration files of each modules
     */
    void loadModules(const std::string &directoryPath);

    /**
     * @brief Process a context into the pipeline.
     * 
     * This function is thread-safe as long as modules are thread safe so keep it in mind when implementing your modules.
     */
    void runPipeline(Context &&context);

    /**
     * @brief Get internal loaded modules
     */
    [[nodiscard]] ModuleList &getModules(void) noexcept { return _modules; }

    /**
     * @brief Get internal loaded modules (const)
     */
    [[nodiscard]] const ModuleList &getModules(void) const noexcept { return _modules; }

    /**
     * @brief Trigger load callback for each module
     */
    void loadModulesConfigurations(const std::string &directoryPath);

    /**
     * @brief Emplaces a new module in the pipeline.
     * 
     *  This function should be called by the onLoadModules callback of your derived pipeline.
     */
    template<typename ...Args, typename Type>
    void addModule(Args &&...args) { _modules.emplace_back(std::make_shared<Type>(std::forward<Args>(args)...)); }

    /**
     * @brief Find a module of Type in internal module list returning it as a shared pointer.
     */
    template<typename Type = IModule>
    std::shared_ptr<Type> findModule(void) const;

protected:
    /**
     * @brief This callback should be redefined to load modules in given directory.
     */
    virtual void onLoadModules(const std::string &directoryPath) = 0;

private:
    ModuleList _modules;
    PipelineMap _pipeline;
    LoggerList _loggers;

    /**
     * @brief Check if every modules dependencies are present.
     */
    void checkModulesDependencies(void);

    /**
     * @brief Check if a module's dependency matches a currently loaded module
     */
    void checkModuleDependency(const ModulePtr &module, const char *dependency);

    /**
     * @brief Create internal pipeline with the current internal modules.
     */
    void createPipeline(void);

    /**
     * @brief Trigger every callback of a given context's state
     */
    void triggerContextStateCallbacks(Context &context);

    /**
     * @brief Inserts a callback handler into the pipeline with given state and priority
     */
    void onRegister(State state, Priority priority, CallbackHandler &&handler);
};

#include "APipeline.ipp"