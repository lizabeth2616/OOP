cmake_minimum_required(VERSION 3.26)

cmake_policy(PUSH)

enable_testing()

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_forced_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/test_lab.cc"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

add_executable(
	lab-test
	${sources}
)

if(MSVC)
	target_compile_options(
		lab-test
		PRIVATE /W4
		PRIVATE /MP
	)
endif()

target_link_libraries(
	lab-test
	GTest::gtest_main
	GTest::gmock_main
	task-lib
)

include(GoogleTest)
gtest_discover_tests(lab-test)

set_target_properties(gtest_main PROPERTIES FOLDER "vendor")
set_target_properties(gtest PROPERTIES FOLDER "vendor")
set_target_properties(gmock_main PROPERTIES FOLDER "vendor")
set_target_properties(gmock PROPERTIES FOLDER "vendor")

cmake_policy(POP)
