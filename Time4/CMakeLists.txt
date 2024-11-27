cmake_minimum_required(VERSION 3.5)

project(time LANGUAGES CXX)

add_subdirectory(time)
add_executable(main main.cpp)

target_link_libraries(main PRIVATE Time)
