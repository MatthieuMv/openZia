/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Logger abstraction
*/

#pragma once

#include <sstream>

#include "ILogger.hpp"

namespace oZ { class Log; }

class oZ::Log
{
public:
    /**
     * @brief Construct a new Log object
     */
    Log(void) = default;

    /**
     * @brief Construct a new Log object using a log level
     */
    Log(Level level) : _level(level) {}

    /**
     * @brief Destroy the Log object and flush stream
     */
    ~Log(void) { flush(); }

    /**
     * @brief Add a value of any type to the stream
     */
    template<typename Type>
    Log &operator<<(Type &&value);

    /**
     * @brief Flush current stream
     */
    Log &flush(void);

    /**
     * @brief Add a new logger into the list
     */
    static void AddLogger(LoggerPtr logger) { GetLoggerList().emplace_back(std::move(logger)); }

    /**
     * @brief Get the global logger list
     */
    static LoggerList &GetLoggerList(void);


private:
    Level _level = Level::Information;
    std::ostringstream _os {};
};

#include "Log.ipp"