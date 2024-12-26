cmake_minimum_required(VERSION 3.5)


add_library(GameClasses STATIC "./source/game_objects.cpp" "./include/game_objects.hpp")
add_library(Interface STATIC "./source/game_interface.cpp" "./include/game_interface.hpp")


