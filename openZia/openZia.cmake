cmake_minimum_required(VERSION 3.0)
project(openZia)

# This modules builds the API library
# It can be imported to easily add the API to an existing CMake project

# Requires C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17 ON)

# Retreive where is located 'openZia.cmake'
get_filename_component(OpenZiaSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

# Define external variables in order to link with ease
set(openZiaLibs openZia)
set(openZiaIncludes ${OpenZiaSourcesDir}/..)

# Library sources
set(OpenZiaSources
    ${OpenZiaSourcesDir}/ByteArray.hpp
    ${OpenZiaSourcesDir}/Endpoint.hpp
    ${OpenZiaSourcesDir}/Endpoint.cpp

    ${OpenZiaSourcesDir}/Packet.hpp
    ${OpenZiaSourcesDir}/Context.hpp
    ${OpenZiaSourcesDir}/Context.cpp

    ${OpenZiaSourcesDir}/IModule.hpp
    ${OpenZiaSourcesDir}/IModule.cpp
    ${OpenZiaSourcesDir}/ILogger.hpp

    ${OpenZiaSourcesDir}/OperatingSystem.hpp
    ${OpenZiaSourcesDir}/DynamicLoader.hpp
    ${OpenZiaSourcesDir}/DynamicLoader.cpp

    ${OpenZiaSourcesDir}/Pipeline.hpp
    ${OpenZiaSourcesDir}/Pipeline.cpp
    ${OpenZiaSourcesDir}/Pipeline.ipp

    ${OpenZiaSourcesDir}/Log.hpp
    ${OpenZiaSourcesDir}/Log.cpp
    ${OpenZiaSourcesDir}/Log.ipp

    ${OpenZiaSourcesDir}/BaseHTTP.hpp
    ${OpenZiaSourcesDir}/HTTP.hpp
    ${OpenZiaSourcesDir}/HeaderHTTP.hpp
    ${OpenZiaSourcesDir}/HeaderHTTP.ipp
    ${OpenZiaSourcesDir}/RequestHTTP.hpp
    ${OpenZiaSourcesDir}/ResponseHTTP.hpp
)

# Create openZia library
add_library(${PROJECT_NAME} ${OpenZiaSources})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# GCC < 9 requires explicit link to filesystem library
if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
    target_compile_options(${PROJECT_NAME} PRIVATE
#        -Werror # Stop on any error !
        -Wall -Wextra
    )
endif ()

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} stdc++fs)

    target_compile_options(${PROJECT_NAME} PRIVATE
#        -Werror # Stop on any error !
        -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy
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