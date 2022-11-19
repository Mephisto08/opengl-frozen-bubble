cmake_minimum_required(VERSION 3.15)
project(HMI)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        HMI
        Color.h
        Graph.h
        Graph.cpp
        Node.h
        Node.cpp
        main.cpp
)