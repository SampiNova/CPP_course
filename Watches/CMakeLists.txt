cmake_minimum_required(VERSION 3.5)

project(watches LANGUAGES CXX)

add_subdirectory(time)
add_subdirectory(watches)
add_executable(main main.cpp)

target_link_libraries(main PRIVATE Time Watches)
