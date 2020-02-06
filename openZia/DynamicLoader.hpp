/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** DynamicLoader
*/

#pragma once

#include <string>
#include <unordered_map>

#include "OperatingSystem.hpp"

#if defined(SYSTEM_LINUX)
#include <dlfcn.h>
#elif defined(SYSTEM_WINDOWS)
#include <Windows.h>
#endif

namespace oZ
{
    class DynamicLoader;

#if defined(SYSTEM_WINDOWS)
    using DynamicHandler = HMODULE;
#else
    using DynamicHandler = void*;
#endif
}

class oZ::DynamicLoader
{
public:
    /**
     * @brief Construct a new Dynamic Loader object
     */
    DynamicLoader(void) = default;

    /**
     * @brief Destroy the Dynamic Loader object and release its content
     */
    ~DynamicLoader(void);

    /**
     * @brief Load a dynamic library
     */
    [[nodiscard]] DynamicHandler load(const std::string &path);

    /**
     * @brief Get a function of handler library, returning opaque pointer
     */
    [[nodiscard]] void *getFunction(DynamicHandler handler, const std::string &name);

    /**
     * @brief Get a function of handler library, returning custom Signature
     */
    template<typename Signature>
    [[nodiscard]] Signature getFunction(DynamicHandler handler, const std::string &name) { return reinterpret_cast<Signature>(getFunction(handler, name)); }

    /**
     * @brief Release loaded libraries.
     *  Call this function after every instances aquired from libraries are destroyed.
     *  If you destroy instances after, the virtual destructor will be unloaded and your program will crash.
     */
    void release(void);

    /**
     * @brief Get the last error as string
     */
    [[nodiscard]] std::string getLastError(void) const noexcept;

    /**
     * @brief Get the name of a handler
     */
    [[nodiscard]] std::string getHandlerPath(const DynamicHandler handler) const noexcept;

private:
    std::unordered_map<DynamicHandler, std::string> _handlers {};
};