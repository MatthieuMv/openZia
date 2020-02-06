cmake_minimum_required(VERSION 3.0)
project(openZia)

# This file is used to compile openZia as a separate CMake project

include(openZia/openZia.cmake)

if (${OPENZIA_TESTS} AND ${OPENZIA_COVERAGE})
    include(Tests/Tests.cmake)
endif ()