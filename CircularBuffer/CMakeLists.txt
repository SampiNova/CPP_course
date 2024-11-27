cmake_minimum_required(VERSION 3.5)

project(circular_buffer LANGUAGES CXX)

option(MAKE_TEST "Making unit tests" ON)
message("MAKE_TEST: ${MAKE_TEST}")

add_subdirectory(CircularBuffer)
if (${MAKE_TEST})
	add_subdirectory(test)
else()
endif()
add_executable(main main.cpp)

target_link_libraries(main PRIVATE CircularBuffer)

