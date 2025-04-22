cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(include)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

list(APPEND SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
add_executable(main_${PROJECT_NAME} ${SRC_FILES})
add_library(${PROJECT_NAME}_lib STATIC ${SRC_FILES})
enable_testing()

add_executable(test_${PROJECT_NAME} tests/unit.cpp)
target_link_libraries(test_${PROJECT_NAME} PRIVATE gtest_main ${PROJECT_NAME}_lib)


include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})