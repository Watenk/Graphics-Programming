
cmake_minimum_required(VERSION 3.25.0)
project(Glad)

add_library(glad include/glad/glad.h src/glad.c include/KHR/khrplatform.h)
target_include_directories(glad PUBLIC include/)
target_include_directories(glad PUBLIC src/)