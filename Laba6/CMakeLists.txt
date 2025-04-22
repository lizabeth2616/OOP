cmake_minimum_required(VERSION 3.10)
project(gtest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(main_${PROJECT_NAME} main.cpp)

enable_testing()

add_executable(test_${PROJECT_NAME} test/unit.cpp)
target_link_libraries(test_${PROJECT_NAME} PRIVATE gtest_main)


include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})
