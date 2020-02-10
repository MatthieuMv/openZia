/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** OperatingSystem
*/

#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(_LINUX)
    #define SYSTEM_LINUX
    #define SHARED_LIB_EXT ".so"
#elif defined(__APPLE__)
    #define SYSTEM_DARWIN
    #define SHARED_LIB_EXT ".dylib"
#elif defined(_WIN32) || defined(_WIN64)
    #define SYSTEM_WINDOWS
    #define SHARED_LIB_EXT ".dll"
#else
    #error "Operating System not supported by openZia"
#endif