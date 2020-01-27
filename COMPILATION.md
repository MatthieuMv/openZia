# Compilation

In this section we will cover the compilation part of openZia. We will see how to compile it independently, how to add it to your actual CMake project and how to automate module compilation.

## Independent compilation

You may first want to assert that openZia compiles well in your system.
The first dependency is to check your C++ compiler, it must be able to support **all C++17 features**. You must also have **CMake** installed with a lower build system like **Makefiles** or **Visual studio solutions**.
If you wish to start unit tests, you must install **Criterion** unit-testing library.
For the coverage, you will need **gcovr**.

First, you need to clone the repository and create a build directory:
```console
git clone git https://github.com/MatthieuMv/openZia.git
cd openZia && mkdir Build && cd Build
```

Then, for a simple library build use the following commands
```console
cmake ..
cmake --build .
```
If you want to run test or see coverage please watch below.

## Add openZia to your CMake project

First you need add openZia's repository to your submodules.
```console
git submodule add https://github.com/MatthieuMv/openZia.git
```

Next you need to **automate compilation** of openZia in your **CMakeLists.txt**, and link your program to it.
```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(Server)

# Include directly the openZia.cmake to your CMake build
# This include gives 'openZiaLibs' and 'openZiaIncludes' variables.
include(openZia/openZia/openZia.cmake)

# Create the executable and link openZia library to it
add_executable(Server main.cpp)
target_link_libraries(Server ${openZiaLibs})
target_include_directories(Server PRIVATE ${openZiaIncludes}))
```

## Automate module compilation

A good practice is to create a directory for each module, and include their **.cmake** file individually.
I assume you already included **openZia.cmake** in your **CMakeLists.txt** and that you have created a directory named **Template** which contains the following **Template.cmake**, **Template.hpp** and **Template.cpp**.
```cmake
# Template.cmake
project(Template)

# Save this directory as TemplateSourcesDir
get_filename_component(TemplateSourcesDir ${CMAKE_CURRENT_LIST_FILE}  PATH)

set(TemplateSources
	${TemplateSourcesDir}/Template.hpp
	${TemplateSourcesDir}/Template.cpp
)

# Compile the module, and link it to openZia
add_library(${PROJECT_NAME} SHARED ${TemplateSources})
target_link_libraries(${PROJECT_NAME} ${openZiaLibs})
target_include_directories(${PROJECT_NAME} PRIVATE ${openZiaIncludes})

# Copy the library into the binary modules directory
set_target_properties(${PROJECT_NAME} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/Modules}
)
```

## Unit tests and code coverage

If you want to start unit tests replace independent build instruction by:
```console
cmake .. -DOPENZIA_TESTS=TRUE
cmake --build .
./openZiaTests
```

If you want code coverage then:
```console
cmake .. -DOPENZIA_TESTS=TRUE -DOPENZIA_COVERAGE=TRUE
cmake --build .
./openZiaTests
cd ..
gcovr --exclude Tests
```