project(openZiaTests)

# Retreive where is located 'Tests.cmake'
get_filename_component(OpenZiaSourcesTestsDir ${CMAKE_CURRENT_LIST_FILE} PATH)

message("Compiling criterion unit-tests for openZia project")

set(TestsSources
    ${OpenZiaSourcesTestsDir}/tests_BaseHTTP.cpp
    ${OpenZiaSourcesTestsDir}/tests_HTTP.cpp
    ${OpenZiaSourcesTestsDir}/tests_Context.cpp
    ${OpenZiaSourcesTestsDir}/tests_IModule.cpp
    ${OpenZiaSourcesTestsDir}/tests_APipeline.cpp
)

add_executable(${PROJECT_NAME} ${TestsSources})
target_link_libraries(${PROJECT_NAME} ${OpenZiaLibs} criterion)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenZiaIncludes})