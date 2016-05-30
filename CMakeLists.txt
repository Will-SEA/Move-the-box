cmake_minimum_required(VERSION 3.5)
project(Move_The_Box)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Board.cpp Board.h Box.cpp Box.h board.txt)
add_executable(Move_The_Box ${SOURCE_FILES})