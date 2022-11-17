cmake_minimum_required(VERSION 3.23)
project(opengl_frozen_bubble)

message(STATUS "start running cmake...")

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(${PROJECT_NAME}
        Board.cpp
        Board.h
        Bubble.cpp
        Bubble.h
        main.cpp)

target_link_libraries(${PROJECT_NAME})

