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
    ${OpenZiaSourcesDir}/HeaderHTTP.cpp
    ${OpenZiaSourcesDir}/RequestHTTP.hpp
    ${OpenZiaSourcesDir}/ResponseHTTP.hpp
)

# Create openZia library
add_library(${PROJECT_NAME} ${OpenZiaSources})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# GCC < 9 requires explicit link to filesystem library
if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} stdc++fs)
endif ()