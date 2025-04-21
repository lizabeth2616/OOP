cmake_minimum_required(VERSION 3.26)

project(lab3)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED)

add_subdirectory("shapes")

add_library(lab::shapes ALIAS shapes)

add_subdirectory("src")

enable_testing()
add_subdirectory("test")