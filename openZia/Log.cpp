/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** Log
*/

#include <iostream>

#include "Log.hpp"

using namespace oZ;

Log &Log::flush(void)
{
    auto &loggers = GetLoggerList();
    auto toLog = _os.str();

    if (loggers.empty())
        std::cout << toLog << std::endl;
    for (auto &logger : loggers)
        logger->onLog(_level, toLog);
    _os.clear();
    return *this;
}

LoggerList &Log::GetLoggerList(void)
{
    static LoggerList loggers;

    return loggers;
}