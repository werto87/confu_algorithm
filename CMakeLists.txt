cmake_minimum_required(VERSION 3.27)
project(project VERSION 1.0.0
        DESCRIPTION project
        LANGUAGES CXX
        )
include(cmake/Cache.cmake)
set(PROJECT_WARNINGS project_warning)
add_library(${PROJECT_WARNINGS} INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_WARNINGS})
set(PROJECT_OPTIONS project_options)
add_library(${PROJECT_OPTIONS} INTERFACE)
target_compile_features(${PROJECT_OPTIONS} INTERFACE cxx_std_20)
include(cmake/StaticAnalyzers.cmake)
include(cmake/Sanitizers.cmake)
enable_sanitizers(${PROJECT_OPTIONS})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_NAME_LIB confu_algorithm)
add_library(${TARGET_NAME_LIB} INTERFACE)
add_subdirectory(confu_algorithm)
target_link_libraries(${TARGET_NAME_LIB} INTERFACE
        ${PROJECT_WARNINGS}
        ${PROJECT_OPTIONS}
        )
####### create executable
OPTION(BUILD_TESTS "enable tests" OFF)
IF (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
ENDIF (BUILD_TESTS)
