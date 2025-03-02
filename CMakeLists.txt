cmake_minimum_required(VERSION 3.26.0)
project(glcraft  VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(glcraft
    src/config.cpp
    src/main.cpp
    src/camera/camera.cpp
    src/mesh/block.cpp
    src/world_generation/chunk.cpp
    src/shaders/shader.cpp
    src/textures/texture.cpp
    src/glad.c
)

target_include_directories(glcraft PRIVATE dependencies)

target_link_libraries(glcraft glfw OpenGL::GL)