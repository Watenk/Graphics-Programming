#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Time.h"
#include "InputHandler.h"
#include "PlayerController.h"
#include "GameObject.h"

const char* WINDOWNAME = "Unreal Engine 6";
const unsigned int WINDOWWIDTH = 1280;
const unsigned int WINDOWHEIGHT = 720;

/* Forward Declaration */
int initGLFW(GLFWwindow* &window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void printVec3(glm::vec3 vec3);

/* Managers */
GLFWwindow* window;
InputHandler* input;
Watenk::Time* watenkTime;
PlayerController* player;
Camera* cam;

int main(){

    /* GLFW Setup */
    int initCode = initGLFW(window);
    if (initCode != 0) return initCode;

    /* Configure GLFW */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    /* Configure OpenGL */
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe Mode
    glEnable(GL_DEPTH_TEST); // Enable Depth Test
    // Cull backfaces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /* Add Managers */
    input = new InputHandler(window);
    watenkTime = new Watenk::Time();
    cam = new Camera(WINDOWWIDTH, WINDOWHEIGHT, POSITION, 90.0f, 0.1f, 1000.0f);
    player = new PlayerController(input, watenkTime, cam, 5.0f);

    /* GameObjects */
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

    Mesh* crateMesh = new Mesh(GL_STATIC_DRAW, vertexData, sizeof(vertexData), sizeof(attributeLenghts) / sizeof(int), attributeLenghts, sizeof(indices) / sizeof(unsigned int), indices);
    Shader* mvpTextureBlendShader = new Shader("res/shaders", "mvpTextureBlend");
    Texture2D* crateTexture = new Texture2D("res/textures/crate.jpg", GL_RGB);
    Texture2D* smileTexture = new Texture2D("res/textures/smile.png", GL_RGBA);
    std::vector<Texture2D*> crateTextures;
    crateTextures.push_back(crateTexture);
    crateTextures.push_back(smileTexture);

    GameObject* crate = new GameObject(crateMesh, mvpTextureBlendShader, crateTextures, cam);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Managers */
        input->update(window);
        watenkTime->update();

        /* Buffers */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // Draw ----------------

        crate->draw();

        // Draw end -----------

        glfwSwapBuffers(window);
        glfwPollEvents(); // Windows Window Events
    }

    glfwTerminate();

    /* Objects */
    delete(crate);

    /* managers */
    delete(input);
    delete(watenkTime);
    delete(player);
    return 0;
}

int initGLFW(GLFWwindow* &window){

    /* Init Lib */
    if (!glfwInit()) return -1;

    /* Winow Hints */ 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */ 
    window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, WINDOWNAME, NULL, NULL);
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