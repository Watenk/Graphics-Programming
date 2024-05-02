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
         // positions         // colors          // UV
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    int attributeLenghts[] = {
        // Pos    // Color    //UV
        3,        3,          2,
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

    Shader textureTestShader("res/shaders", "textureTest");
    textureTestShader.bind();
    glUniform1i(glGetUniformLocation(textureTestShader.getShaderProgramID(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(textureTestShader.getShaderProgramID(), "texture2"), 1);

    Mesh quadMesh(GL_STATIC_DRAW, vertexData, sizeof(vertexData), 3, attributeLenghts, 6, indices);

    // Wireframe Mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
        processInput(window);

        // // RotateScaleTranslate
        // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
        // vec = trans * vec;
        // std::cout << vec.x << vec.y << vec.z << std::endl;

        // Draw ----------------

        quadMesh.bind();
        textureTestShader.bind();

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