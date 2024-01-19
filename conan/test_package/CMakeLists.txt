cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(confu_algorithm CONFIG REQUIRED)


add_executable(example src/example.cpp)
target_link_libraries(example confu_algorithm::confu_algorithm)
