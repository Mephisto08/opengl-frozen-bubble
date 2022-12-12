cmake_minimum_required(VERSION 3.0)
project(Frozen-Bubble)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        src/main.cpp
        framework/OBJLoader.cpp
        src/SceneElements/Camera.cpp
        src/SceneElements/Renderable.cpp
        src/SceneElements/Mesh.cpp
        src/SceneElements/Transform.cpp
        )

include_directories(
        src
        framework
        src/SceneElements
)

add_executable(Frozen-Bubble ${SOURCES})

target_link_libraries(Frozen-Bubble EGL GLESv2 X11 png)