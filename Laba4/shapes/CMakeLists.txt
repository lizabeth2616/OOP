cmake_minimum_required(VERSION 3.26)

add_library(shapes INTERFACE)

target_sources(
	shapes
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/Shapes.h
	${CMAKE_CURRENT_SOURCE_DIR}/Array.h
)

target_include_directories(
	shapes
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
