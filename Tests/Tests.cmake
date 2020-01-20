project(openZiaTests)

# Retreive where is located 'Tests.cmake'
get_filename_component(OpenZiaSourcesTestsDir ${CMAKE_CURRENT_LIST_FILE} PATH)

message("Compiling criterion unit-tests for openZia project")

set(TestsSources
    ${OpenZiaSourcesTestsDir}/tests_BaseHTTP.cpp
    ${OpenZiaSourcesTestsDir}/tests_HeaderHTTP.cpp
    ${OpenZiaSourcesTestsDir}/tests_ResponseHTTP.cpp
    ${OpenZiaSourcesTestsDir}/tests_RequestHTTP.cpp
    ${OpenZiaSourcesTestsDir}/tests_Endpoint.cpp
    ${OpenZiaSourcesTestsDir}/tests_Context.cpp
    ${OpenZiaSourcesTestsDir}/tests_IModule.cpp
    ${OpenZiaSourcesTestsDir}/tests_ILogger.cpp
    ${OpenZiaSourcesTestsDir}/tests_Pipeline.cpp
    ${OpenZiaSourcesTestsDir}/tests_Log.cpp
)

add_executable(${PROJECT_NAME} ${TestsSources} ${OpenZiaSources})
target_link_libraries(${PROJECT_NAME} criterion)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenZiaIncludes})

if (DEFINED OPENZIA_COVERAGE)
    target_link_libraries(${PROJECT_NAME} gcov)
    target_compile_options(${PROJECT_NAME} PUBLIC --coverage)
endif ()