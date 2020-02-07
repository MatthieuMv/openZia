cmake_minimum_required(VERSION 3.0)

if (NOT DEFINED PROJECT_NAME)
    project(openZia)
endif()

# This modules builds the API library
# It can be imported to easily add the API to an existing CMake project

# Retreive where is located 'openZia.cmake'
get_filename_component(OpenZiaSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

# Define external variables in order to link with ease
set(openZiaLibs openZia)
set(openZiaIncludes ${OpenZiaSourcesDir}/..)

# Library sources
set(OpenZiaSources
    ${OpenZiaSourcesDir}/Endpoint.cpp
    ${OpenZiaSourcesDir}/Context.cpp
    ${OpenZiaSourcesDir}/IModule.cpp
    ${OpenZiaSourcesDir}/DynamicLoader.cpp
    ${OpenZiaSourcesDir}/Pipeline.cpp
    ${OpenZiaSourcesDir}/Log.cpp
    ${OpenZiaSourcesDir}/HeaderHTTP.cpp
)

# Create openZia library
add_library(${openZiaLibs} ${OpenZiaSources})

if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY MATCHES "")
    add_definitions(-DLIBDIR="${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif()
if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY MATCHES "")
    add_definitions(-DBINDIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()

set_property(TARGET ${openZiaLibs} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${openZiaLibs} PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${openZiaLibs} PROPERTY POSITION_INDEPENDENT_CODE ON)

# GCC < 9 requires explicit link to filesystem library
if (UNIX)
    target_link_libraries(${openZiaLibs} ${CMAKE_DL_LIBS} stdc++fs)
    target_compile_options(${openZiaLibs} PRIVATE
#        -Werror # Stop on any error !
        -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy
        -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations
        -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual
        -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel
        -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
        -Weffc++ -pedantic-errors -Wconversion -Wfloat-equal
        -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winline
        -Winvalid-pch -Wlong-long -Wmissing-field-initializers -Wmissing-format-attribute
        -Wmissing-noreturn -Wpacked -Wpointer-arith -Wstack-protector
        -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter
        -Wvariadic-macros -Wwrite-strings -Wunused-variable
    )
endif ()