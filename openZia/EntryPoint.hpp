/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** EntryPoint
*/

#ifndef ENTRYPOINT_HPP_
# define ENTRYPOINT_HPP_

# include "OperatingSystem.hpp"

# ifndef EXTERN_C
#  ifdef __cplusplus
#   define EXTERN_C extern "C"
#  else
#   define EXTERN_C extern
#  endif
# endif

# if defined(SYSTEM_LINUX)
#  define OPEN_ZIA_EXPORT
# elif defined(SYSTEM_WINDOWS)
#  define OPEN_ZIA_EXPORT __declspec(dllexport) __stdcall
# endif

# define STR_VALUE(arg) #arg
# define FUNCTION_NAME(name) STR_VALUE(name)

# define OPEN_ZIA_ENTRY_POINT CreateModule
# define OPEN_ZIA_ENTRY_POINT_AS_STRING FUNCTION_NAME(OPEN_ZIA_ENTRY_POINT)

/**
 * @brief Shortcut to create a function entry point of your module
 */
# define OPEN_ZIA_MAKE_ENTRY_POINT(class)                           \
    EXTERN_C OPEN_ZIA_EXPORT oZ::IModule *OPEN_ZIA_ENTRY_POINT()    \
    {                                                               \
        return new class();                                         \
    }                                                               \

#endif /* !ENTRYPOINT_HPP_ */
