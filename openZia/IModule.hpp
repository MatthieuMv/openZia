/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module interface
*/

#pragma once

#include <memory>
#include <vector>

#include "Context.hpp"

namespace oZ
{
    class IModule;
    class Pipeline;

    /**
     * @brief Priority enum, used to sort modules in the pipeline.
     *
     * If you need to sort modules with more precision, you can use intermediate offset.
     * Example: Low + 1, Low + 2, ...
     */
    enum Priority : std::uint16_t {
        Last = 0,
        Independent = 1000,
        Low = 2000,
        Medium = 3000,
        High = 4000,
        ASAP = 5000
    };

    /**
     * @brief Module pointer type, using shared_ptr as backend.
     */
    using ModulePtr = std::shared_ptr<IModule>;

    /**
     * @brief Function signature that each module should respect to get detected and instantied.
     * It musts uses the name 'createModule'.
     *
     * Example : IModule *CreateModule(void) { return MyModule(); }
     */
    using ModuleInstanceFunction = IModule*(*)(void);
}

/**
 * @brief This class is the interface of every module.
 *
 * Each module can reimplement a set of virtual functions at each callback of the pipeline.

 * Pipeline callbacks get a Context reference in order to transform and/or use its state.
 */
class oZ::IModule
{
public:
    /**
     * @brief Dependencies are represented as a vector of raw string
     */
    using Dependencies = std::vector<const char *>;

    /**
     * @brief Construct a new IModule object
     */
    IModule(void) = default;

    /**
     * @brief Destroy the IModule object
     */
    virtual ~IModule(void) = default;

    /**
     * @brief Get the module name
     */
    virtual const char *getName(void) const = 0;

    /**
     * @brief Register module's callbacks in the pipeline
     */
    virtual void onRegisterCallbacks(Pipeline &) = 0;

    /**
     * @brief Get the module dependencies
     *
     *  By default a module has no dependencies
     */
    virtual Dependencies getDependencies(void) const noexcept { return Dependencies(); }

    /**
     * @brief This function is called once module registered their callbacks
     *
     *  There you should (if needed) implement dependencies search
     *  Be careful, at this point other modules may not have retreived their dependencies !
     *  Use the pipeline only to find your dependencies and store their shared_ptr instances
     *
     *  This function is not pure virtual because you may not need it
     */
    virtual void onRetreiveDependencies(Pipeline &pipeline);

    /**
     * @brief This function is called after module retreived its dependencies.
     *
     *  The given directory is the path to configuration files
     *
     *  This function is not pure virtual because you may not need it
     */
    virtual void onLoadConfigurationFile(const std::string &directory);

    /**
     * @brief Callback used to intercept client connections
     */
    virtual void onConnection(const FileDescriptor fd, const Endpoint endpoint, bool useEncryption = false);

    /**
     * @brief Callback used to intercept client disconnections
     */
    virtual void onDisconnection(const FileDescriptor fd, const Endpoint endpoint);
};
