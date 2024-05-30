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
std::vector<float> getCubeVertices();
std::vector<int> getCubeAttributeLenghts();
std::vector<unsigned int> getCubeIndices();

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
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    /* Add Managers */
    input = new InputHandler(window);
    watenkTime = new Watenk::Time();
    cam = new Camera(WINDOWWIDTH, WINDOWHEIGHT, POSITION, 90.0f, 0.1f, 1000.0f);
    player = new PlayerController(input, watenkTime, cam, 5.0f);

    /* Meshes */
    Mesh* cubeMesh = new Mesh(GL_STATIC_DRAW, getCubeVertices(), getCubeAttributeLenghts(), getCubeIndices());

    /* Shaders */
    Shader* crateShader = new Shader("res/shaders", "phongMvp");
    Shader* lightSourceShader = new Shader("res/shaders", "ColorMvp");

    /* Textures */
    std::vector<Texture2D*> noTextures;

    std::vector<Texture2D*> crateTextures;
    Texture2D* container = new Texture2D("res/textures/container.png", GL_RGBA);
    Texture2D* containerSpecular = new Texture2D("res/textures/containerSpecular.png", GL_RGBA);
    crateTextures.push_back(container);
    crateTextures.push_back(containerSpecular);

    /* GameObjects */
    GameObject* crate = new GameObject(cubeMesh, crateShader, crateTextures, cam);
    GameObject* lightSource = new GameObject(cubeMesh, lightSourceShader, noTextures, cam);

    /* Scene Positions */
    lightSource->transform.position = glm::vec3(1.2f, 1.0f, 2.0f);
    lightSource->transform.size = glm::vec3(0.2f);

    /* Scene Settings */
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    /* Color uniforms */
    lightSource->shader->setVec4("color", glm::vec4(lightColor.x, lightColor.y, lightColor.z, 1.0f));

    /* Light uniforms */
    crate->shader->setVec3("light.position", lightSource->transform.position);
    crate->shader->setVec3("light.ambientStrenght", glm::vec3(0.2f, 0.2f, 0.2f));
    crate->shader->setVec3("light.diffuseStrenght", glm::vec3(0.5f, 0.5f, 0.5f));
    crate->shader->setVec3("light.specularStrenght", glm::vec3(1.0f)); 
    crate->shader->setFloat("light.constant", 1.0f);
    crate->shader->setFloat("light.linear", 0.09f);
    crate->shader->setFloat("light.quadratic", 0.032f);	

    /* Material uniforms */
    crate->shader->setInt("material.diffuseTexture", 0);
    crate->shader->setInt("material.specularTexture", 1);
    crate->shader->setFloat("material.shininess", 64.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Managers */
        input->update(window);
        watenkTime->update();

        /* GameObject Updates */
        crate->transform.rotate(glm::vec3(0.0f, 10.0f * watenkTime->getDeltaTime(), 20.0f * watenkTime->getDeltaTime()));

        /* Uniform Updates */
        crate->shader->setVec3("viewPos", cam->transform.position);

        /* Buffers */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // Draw ----------------

        crate->draw();
        lightSource->draw();

        // Draw end -----------

        glfwSwapBuffers(window);
        glfwPollEvents(); // Windows Window Events
    }

    /* GameObjects */
    delete crate ;
    delete lightSource ;

    /* managers */
    delete input;
    delete watenkTime;
    delete player;

    glfwTerminate();
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

std::vector<float> getCubeVertices(){
    std::vector<float> cubeVertices = {
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

    return cubeVertices;
}

std::vector<int> getCubeAttributeLenghts(){
    std::vector<int> attributeLenghts = {
        // Pos   // UV   // Normals
        3,       2,      3,
    };

    return attributeLenghts;
}

std::vector<unsigned int> getCubeIndices(){
    std::vector<unsigned int> cubeIndices = {
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

    return cubeIndices;
}