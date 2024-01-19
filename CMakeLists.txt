cmake_minimum_required(VERSION 3.27)
project(project VERSION 1.0.0
        DESCRIPTION project
        LANGUAGES CXX
        )
cmake_policy(SET CMP0015 NEW)
include(cmake/Cache.cmake)
find_package(Boost REQUIRED)
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
set(TARGET_NAME_LIB project_lib)
add_library(${TARGET_NAME_LIB} INTERFACE)
add_subdirectory(src)
target_link_libraries(${TARGET_NAME_LIB} INTERFACE
        ${PROJECT_WARNINGS}
        ${PROJECT_OPTIONS}
        Boost::headers
        Boost::json
        )

enable_testing()
add_subdirectory(test)