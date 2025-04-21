cmake_minimum_required(VERSION 3.26)

add_library(alloc INTERFACE)

target_sources(
	alloc
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/LinkedList.h
	${CMAKE_CURRENT_SOURCE_DIR}/Allocator.h
)

target_include_directories(
	alloc
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
