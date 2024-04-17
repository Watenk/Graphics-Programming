
# This is the Learn-OpenGL CMake file
# Make executable named ${PROJECT_NAME} from main.cpp
add_executable(${PROJECT_NAME} src/main.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)
# Lib Linking
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)