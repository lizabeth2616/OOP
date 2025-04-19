cmake_minimum_required(VERSION 3.26)

project(lab2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED)

add_subdirectory("eleven")

add_library(lab::task-lib ALIAS task-lib)

add_subdirectory("src")

enable_testing()
add_subdirectory("test")
