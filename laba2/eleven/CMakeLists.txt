cmake_minimum_required(VERSION 3.26)

add_library(task-lib INTERFACE)

target_sources(
	task-lib
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/Eleven.h
	${CMAKE_CURRENT_SOURCE_DIR}/Eleven.cpp
)

target_include_directories(
	task-lib
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
