
# This is the Learn-OpenGL CMake file
# Make executable named ${PROJECT_NAME} from main.cpp
add_executable(${PROJECT_NAME} src/main.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)
# Lib Linking
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# copy dir to build
add_custom_target(copyResources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res
)

# Ensure the custom command runs before building the target (so changes in res are included in the build)
add_dependencies(${PROJECT_NAME} copyResources)