cmake_minimum_required(VERSION 3.5)

project(Watches)

add_library(Watches STATIC watches.cpp watches.hpp)
target_link_libraries(Watches PUBLIC Time)
