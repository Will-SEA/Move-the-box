cmake_minimum_required(VERSION 3.5)
project(MoveTheBox)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Game.cpp Game.h Board.cpp Board.h)
add_executable(MoveTheBox ${SOURCE_FILES})