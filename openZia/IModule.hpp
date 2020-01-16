/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module interface
*/

#pragma once

#include <memory>

#include "Context.hpp"

namespace oZ
{
    class IModule;

    /**
     * @brief Priority enum, used to sort modules in the pipeline.
     * 
     * If you need to sort modules with more precision, you can use intermediate offset.
     * Example: Low + 1, Low + 2, ...
     */
    enum Priority : std::uint16_t {
        Independent = 0,
        Low = 1000,
        Medium = 2000,
        High = 3000,
        Critical = 4000
    };

    /**
     * @brief Module pointer type, using shared_ptr as backend.
     */
    using ModulePtr = std::shared_ptr<IModule>;

    /**
     * @brief Function signature that each module should respect to get detected and instantied.
     * 
     * This function returns a raw pointer to an IModule to let the implementer choose
     * to encapsulate it under an unique or a shared pointer.
     */
    using ModuleInstanceFunction = IModule*(*)(void);

    /**
     * @brief Callback handler that stores a bounded module's callback function
     */
    using CallbackHandler = std::function<void(Context &)>;

    /**
     * @brief RegisterHandler is a callback function which is used to register callbacks to the pipeline.
     *  This function needs:
     *      1) A pipeline state
     *      2) A priority
     *      3) A callback handler
     */
    using RegisterHandler = std::function<void(State, Priority, CallbackHandler &&)>;
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
    virtual void registerCallbacks(const RegisterHandler &) const = 0;

    /**
     * @brief Get the module dependencies
     * 
     *  By default modules have no dependencies
     */
    virtual Dependencies getDependencies(void) const { return Dependencies(); }
};
