# This is the main CMake file
cmake_minimum_required(VERSION 3.29.0-rc2)
# Project Name
project(Graphics-Programming)

# Add other CMakeLists
add_subdirectory(libs/glfw-3.4)
add_subdirectory(libs/glad)
add_subdirectory(Graphics-Programming)