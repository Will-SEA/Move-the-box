cmake_minimum_required(VERSION 3.5)
project(Move_the_box)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Box.cpp Box.h Board.cpp Board.h Game.cpp Game.h)
add_executable(Move_the_box ${SOURCE_FILES})