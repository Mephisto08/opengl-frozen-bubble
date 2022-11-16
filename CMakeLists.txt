cmake_minimum_required(VERSION 3.17)
project(opengl_frozen_bubble)

set(CMAKE_CXX_STANDARD 14)

add_executable(opengl_frozen_bubble main.cpp Board.cpp Board.h Bubble.cpp Bubble.h)