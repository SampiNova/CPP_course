cmake_minimum_required(VERSION 3.5)

project(Time)

add_library(Time STATIC time.cpp watch.cpp simple_watch.cpp time.hpp)
