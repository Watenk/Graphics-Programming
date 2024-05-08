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

// Forward Declaration
int init(GLFWwindow* &window, const char* windowName);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);

int main(){

    /* GLFW Setup */
    GLFWwindow* window;
    int initCode = init(window, "Graphics Programming");
    if (initCode != 0) return initCode;

    /* Mesh */
    float vertexData[] = {
         // positions         // UV
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
    };

    int attributeLenghts[] = {
        // Pos   //UV
        3,       2,
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

    Texture2D crateTexture("res/textures/crate.jpg", GL_RGB, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Texture2D smileTexture("res/textures/smile.png", GL_RGBA, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Shader modelViewProjection("res/shaders", "modelViewProjection");
    modelViewProjection.bind();
    glUniform1i(glGetUniformLocation(modelViewProjection.getID(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(modelViewProjection.getID(), "texture2"), 1);

    Mesh quadMesh(GL_STATIC_DRAW, vertexData, sizeof(vertexData), 2, attributeLenghts, 6, indices);

    // Transformation matrices
    glm::mat4 model = glm::mat4(1.0f); // Model Matrix
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotation applied to moddel matrix
    glm::mat4 view = glm::mat4(1.0f); // View Matrix
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Translation applied to view matrix (its camera movement) - (note that we're translating the scene in the reverse direction of where we want to move)
    glm::mat4 projection; // Projection Matrix
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Perspective

    // Wireframe Mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
        processInput(window);

        // Draw ----------------

        quadMesh.bind();
        modelViewProjection.bind();
        // // RotateScaleTranslate
        glUniformMatrix4fv(glGetUniformLocation(modelViewProjection.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(modelViewProjection.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(modelViewProjection.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        /* Textures */
        glActiveTexture(GL_TEXTURE0);
        crateTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        smileTexture.bind();

        glDrawElements(GL_TRIANGLES, quadMesh.getIndicesAmount(), GL_UNSIGNED_INT, 0);

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