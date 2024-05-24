#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Time.h"
#include "Camera.h"
#include "InputHandler.h"
#include "Transform.h"

// Forward Declaration
int init(GLFWwindow* &window, const char* windowName);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);
void printVec3(glm::vec3 vec3);

Watenk::Time watenkTime;
Camera cam(glm::vec3(0, 0, 5));
InputHandler input;

int main(){

    /* GLFW Setup */
    GLFWwindow* window;
    int initCode = init(window, "Graphics Programming");
    if (initCode != 0) return initCode;

    /* Configure OpenGL */
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe Mode
    glEnable(GL_DEPTH_TEST); // Enable Depth Test

    /* Mesh */
    float vertexData[] = {
        // positions            // tex coords    // normals
        0.5f, -0.5f, -0.5f,      1.f, 0.f,       0.f, -1.f,  0.f,
        0.5f, -0.5f,  0.5f,      1.f, 1.f,       0.f, -1.f,  0.f,
       -0.5f, -0.5f,  0.5f,      0.f, 1.f,       0.f, -1.f,  0.f,
       -0.5f, -0.5f, -0.5f,      0.f, 0.f,       0.f, -1.f,  0.f,

        0.5f,  0.5f, -0.5f,      2.f, 0.f,       1.f,  0.f,  0.f,
        0.5f,  0.5f,  0.5f,      2.f, 1.f,       1.f,  0.f,  0.f,

        0.5f,  0.5f,  0.5f,      1.f, 2.f,       0.f,  0.f,  1.f,
       -0.5f,  0.5f,  0.5f,      0.f, 2.f,       0.f,  0.f,  1.f,

       -0.5f,  0.5f,  0.5f,     -1.f, 1.f,       -1.f, 0.f,  0.f,
       -0.5f,  0.5f, -0.5f,     -1.f, 0.f,       -1.f, 0.f,  0.f,

       -0.5f,  0.5f, -0.5f,      0.f, -1.f,      0.f,  0.f, -1.f,
        0.5f,  0.5f, -0.5f,      1.f, -1.f,      0.f,  0.f, -1.f,

       -0.5f,  0.5f, -0.5f,      3.f, 0.f,       0.f,  1.f,  0.f,
       -0.5f,  0.5f,  0.5f,      3.f, 1.f,       0.f,  1.f,  0.f,

        0.5f, -0.5f,  0.5f,      1.f, 1.f,       0.f,  0.f,  1.f,
       -0.5f, -0.5f,  0.5f,      0.f, 1.f,       0.f,  0.f,  1.f,

       -0.5f, -0.5f,  0.5f,      0.f, 1.f,       -1.f, 0.f,  0.f,
       -0.5f, -0.5f, -0.5f,      0.f, 0.f,       -1.f, 0.f,  0.f,

       -0.5f, -0.5f, -0.5f,      0.f, 0.f,       0.f,  0.f, -1.f,
        0.5f, -0.5f, -0.5f,      1.f, 0.f,       0.f,  0.f, -1.f,

        0.5f, -0.5f, -0.5f,      1.f, 0.f,       1.f,  0.f,  0.f,
        0.5f, -0.5f,  0.5f,      1.f, 1.f,       1.f,  0.f,  0.f,

        0.5f,  0.5f, -0.5f,      2.f, 0.f,       0.f,  1.f,  0.f,
        0.5f,  0.5f,  0.5f,      2.f, 1.f,       0.f,  1.f,  0.f
    };

    int attributeLenghts[] = {
        // Pos   // UV   // Normals
        3,       2,      3,
    };

    unsigned int indices[] = {
        // Down
        0, 1, 2,      // first triangle
        0, 2, 3,      // second triangle
        // Back
        14, 6, 7,     // first triangle
        14, 7, 15,    // second triangle
        // Right
        20, 4, 5,     // first triangle
        20, 5, 21,    // second triangle
        // Left
        16, 8, 9,     // first triangle
        16, 9, 17,    // second triangle
        // Front
        18, 10, 11,   // first triangle
        18, 11, 19,   // second triangle
        // Up
        22, 12, 13,   // first triangle
        22, 13, 23,   // second triangle
    };

    Mesh squareMesh(GL_STATIC_DRAW, vertexData, sizeof(vertexData), sizeof(attributeLenghts) / sizeof(int), attributeLenghts, sizeof(indices) / sizeof(unsigned int), indices);

    /* Shaders */
    Shader mvpShader("res/shaders", "modelViewProjection");
    mvpShader.bind();

    glm::mat4 model = glm::mat4(1.0f); // Model Matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Projection Matrix
    glUniformMatrix4fv(glGetUniformLocation(mvpShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(mvpShader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    /* Textures */
    Texture2D crateTexture("res/textures/crate.jpg", GL_RGB, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Texture2D smileTexture("res/textures/smile.png", GL_RGBA, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    glUniform1i(glGetUniformLocation(mvpShader.getID(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(mvpShader.getID(), "texture2"), 1);

    printVec3(cam.transform.getEuler());
    cam.transform.setRotation(glm::vec3(50, 10, 10));
    printVec3(cam.transform.getEuler());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        // Update Classes
        input.update(window);
        watenkTime.update();
        glm::mat4 view = cam.getViewMatrix();

        // Clear Buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer

        // Draw ----------------

        squareMesh.bind();
        mvpShader.bind();

        /* Transformation matrices */
        glUniformMatrix4fv(glGetUniformLocation(mvpShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(mvpShader.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(mvpShader.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        /* Textures */
        glActiveTexture(GL_TEXTURE0);
        crateTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        smileTexture.bind();

        /* DrawElement */
        glDrawElements(GL_TRIANGLES, squareMesh.getIndicesAmount(), GL_UNSIGNED_INT, 0);

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

void printVec3(glm::vec3 vec3){
    std::cout << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")" << std::endl;
}