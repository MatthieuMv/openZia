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
    enum class Level {
        Information,
        Warning,
        Error,
        Debug
    };

    /**
     * @brief Logger pointer type, using shared_ptr like IModule.
     */
    using LoggerPtr = std::shared_ptr<ILogger>;
}

/**
 * @brief This interface should be derived to implement a custom logger.
 *  It must be loaded like any other Module.
 */
class oZ::ILogger
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
    virtual void log(const std::string &message, Level level = Level::Information) = 0;
};
