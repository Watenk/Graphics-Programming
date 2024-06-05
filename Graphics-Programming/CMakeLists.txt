project(graphics-programming)

# Get a list of all .cpp files in the directory and its subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Add all the .cpp files to the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Lib Linking
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE std-image)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# Copy directory to build
add_custom_target(copyResources
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res
)

# Ensure the custom command runs before building the target (so changes in res are included in the build)
add_dependencies(${PROJECT_NAME} copyResources)