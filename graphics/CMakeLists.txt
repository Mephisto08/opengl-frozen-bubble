cmake_minimum_required(VERSION 3.24)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(graphics main.cpp)
target_link_libraries(graphics EGL GLESv2 X11 png)

add_custom_target(copy_shader COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/shader ${CMAKE_CURRENT_BINARY_DIR}/shader)
add_dependencies(graphics copy_shader)
