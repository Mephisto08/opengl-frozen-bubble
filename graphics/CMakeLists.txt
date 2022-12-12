cmake_minimum_required(VERSION 3.24)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(graphics main.cpp)
target_link_libraries(graphics EGL GLESv2 X11 png)
