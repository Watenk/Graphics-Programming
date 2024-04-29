#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Shader.h"
#include "Mesh.h"

// Forward Declaration
int init(GLFWwindow* &window, const char* windowName);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);

int main(){

    /* GLFW Setup */
    GLFWwindow* window;
    int initCode = init(window, "Graphics Programming");
    if (initCode != 0) return initCode;

    /* Shaders */
    Shader basicShader("res/shaders", "basic");

    /* Mesh */
    float vertexData[] = {
        // Pos                // Color
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right (0)
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right (1)
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left (2)
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,  // top left  (3)
    };

    int attributeLenghts[] = {
        // Pos    // Color
        3,        3,
    };

    unsigned int indices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle

        //  (3)-------(0)
        //   |   \     |
        //   |    \    |
        //   |     \   |
        //  (2)-------(1)
    }; 

    Mesh quadMesh(basicShader, GL_STATIC_DRAW, vertexData, sizeof(vertexData), 2, attributeLenghts, indices, 6);

    // Wireframe Mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
        processInput(window);
        
        // Draw ----------------

        quadMesh.draw();

        // Draw end -----------

        glfwSwapBuffers(window);
        glfwPollEvents(); // Windows Window Events
    }

    glfwTerminate();
    return 0;
}

int init(GLFWwindow* &window, const char* windowName){

    /* Init Lib */
    if (!glfwInit()) return -1;

    /* Winow Hints */ 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */ 
    window = glfwCreateWindow(640, 480, windowName, NULL, NULL);
    if (!window){
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set callback for window size change */
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

    /* Load GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to load GLAD" << std::endl;
        glfwTerminate();
        return -2;
    }
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}