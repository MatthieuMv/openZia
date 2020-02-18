/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Logger Interface
*/

#pragma once

#include <string>

#include "IModule.hpp"

namespace oZ
{
    class ILogger;

    /**
     * @brief Levels of log messages
     */
    enum Level : std::uint8_t {
        Information,
        Warning,
        Critical,
        Debug
    };

    /**
     * @brief Logger pointer type, using shared_ptr like IModule.
     */
    using LoggerPtr = std::shared_ptr<ILogger>;

    /**
     * @brief Simple vector of logger interfaces
     */
    using LoggerList = std::vector<LoggerPtr>;
}

/**
 * @brief This interface should be derived to implement a custom logger.
 *  It must be loaded like any other Module.
 */
class oZ::ILogger : public IModule
{
public:
    /**
     * @brief Construct a new ILogger object
     */
    ILogger(void) = default;

    /**
     * @brief Destroy the ILogger object
     */
    virtual ~ILogger(void) = default;

    /**
     * @brief Log a single message of given level
     */
    virtual void onLog(Level level, const std::string &message) = 0;

    /**
     * @brief The callback register handler is defaulted because your logger may not need it
     */
    virtual void onRegisterCallbacks(Pipeline &) {}
};
