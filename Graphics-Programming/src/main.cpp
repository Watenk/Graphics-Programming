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
#include "Model.h"
#include "lights.h"

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
Lights* lights;

int main(){

    /* GLFW Setup */
    int initCode = initGLFW(window);
    if (initCode != 0) return initCode;

    /* Configure GLFW */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    /* Configure OpenGL */
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe Mode
    glEnable(GL_DEPTH_TEST); // Enable Depth Test
    // Cull backfaces
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    /* Add Managers */
    input = new InputHandler(window);
    watenkTime = new Watenk::Time();
    cam = new Camera(WINDOWWIDTH, WINDOWHEIGHT, POSITION, 90.0f, 0.1f, 1000.0f);
    player = new PlayerController(input, watenkTime, cam, 5.0f);
    lights = new Lights();

    /* Shaders */
    Shader* crateShader = new Shader("res/shaders", "lightsPhongMvp");
    Shader* backpackShader = new Shader("res/shaders", "lightsPhongMvp");
    Shader* skyboxShader = new Shader("res/shaders", "skyboxMvp");

    /* Textures */
    std::vector<Texture2D*> noTextures;

    std::vector<Texture2D*> crateTextures;
    Texture2D* container = new Texture2D("res/textures/container.png", TextureType::diffuse);
    Texture2D* containerSpecular = new Texture2D("res/textures/containerSpecular.png", TextureType::specular);
    crateTextures.push_back(container);
    crateTextures.push_back(containerSpecular);

    /* Meshes */
    Mesh* cubeMesh = new Mesh(GL_STATIC_DRAW, getCubeVertices(), getCubeIndices(), crateTextures, cam);

    /* Models */
    Model* backpack = new Model(GL_STATIC_DRAW, "res/models/backpack/backpack.obj", cam);

    /* Lights */
    lights->addShader(crateShader);
    lights->addShader(backpackShader);

    /* Material uniforms */
    crateShader->setInt("material.diffuseTexture", 0);
    crateShader->setInt("material.specularTexture", 1);
    crateShader->setFloat("material.shininess", 64.0f);

    backpackShader->setInt("material.diffuseTexture", 0);
    backpackShader->setInt("material.specularTexture", 1);
    backpackShader->setFloat("material.shininess", 64.0f);

    for (Mesh* mesh : backpack->meshes){
        mesh->transform.move(glm::vec3(10, 0, 0));
    }

    std::cout << backpack->meshes[0]->textures[1]->texturePath << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Managers */
        input->update(window);
        watenkTime->update();

        /* Uniform Updates */
        skyboxShader->setVec3("viewDirection", cam->transform.getFront());
        crateShader->setVec3("viewPos", cam->transform.position);
        backpackShader->setVec3("viewPos", cam->transform.position);

        /* GameObject Updates */
        cubeMesh->transform.rotate(glm::vec3(0.0f, 10.0f * watenkTime->getDeltaTime(), 20.0f * watenkTime->getDeltaTime()));

        /* Buffers */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw ----------------
        
        /* Skybox */
        glDisable(GL_DEPTH);
        cubeMesh->draw(skyboxShader);
        glEnable(GL_DEPTH);

        cubeMesh->draw(crateShader);
        backpack->draw(backpackShader);

        // Draw end -----------a

        glfwSwapBuffers(window);
        glfwPollEvents(); // Windows Window Events
    }

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
        // positions              // normals             // tex coords  
        0.5f, -0.5f, -0.5f,       0.f, -1.f,  0.f,       1.f, 0.f,     
        0.5f, -0.5f,  0.5f,       0.f, -1.f,  0.f,       1.f, 1.f,     
       -0.5f, -0.5f,  0.5f,       0.f, -1.f,  0.f,       0.f, 1.f,     
       -0.5f, -0.5f, -0.5f,       0.f, -1.f,  0.f,       0.f, 0.f,     

        0.5f,  0.5f, -0.5f,       1.f,  0.f,  0.f,       2.f, 0.f,     
        0.5f,  0.5f,  0.5f,       1.f,  0.f,  0.f,       2.f, 1.f,     
        0.5f,  0.5f,  0.5f,       0.f,  0.f,  1.f,       1.f, 2.f,     
       -0.5f,  0.5f,  0.5f,       0.f,  0.f,  1.f,       0.f, 2.f,     

       -0.5f,  0.5f,  0.5f,       -1.f, 0.f,  0.f,      -1.f, 1.f,     
       -0.5f,  0.5f, -0.5f,       -1.f, 0.f,  0.f,      -1.f, 0.f,     
       -0.5f,  0.5f, -0.5f,       0.f,  0.f, -1.f,       0.f, -1.f,    
        0.5f,  0.5f, -0.5f,       0.f,  0.f, -1.f,       1.f, -1.f,    

       -0.5f,  0.5f, -0.5f,       0.f,  1.f,  0.f,       3.f, 0.f,     
       -0.5f,  0.5f,  0.5f,       0.f,  1.f,  0.f,       3.f, 1.f,     
        0.5f, -0.5f,  0.5f,       0.f,  0.f,  1.f,       1.f, 1.f,     
       -0.5f, -0.5f,  0.5f,       0.f,  0.f,  1.f,       0.f, 1.f,     

       -0.5f, -0.5f,  0.5f,       -1.f, 0.f,  0.f,       0.f, 1.f,     
       -0.5f, -0.5f, -0.5f,       -1.f, 0.f,  0.f,       0.f, 0.f,     
       -0.5f, -0.5f, -0.5f,       0.f,  0.f, -1.f,       0.f, 0.f,     
        0.5f, -0.5f, -0.5f,       0.f,  0.f, -1.f,       1.f, 0.f,     

        0.5f, -0.5f, -0.5f,       1.f,  0.f,  0.f,       1.f, 0.f,     
        0.5f, -0.5f,  0.5f,       1.f,  0.f,  0.f,       1.f, 1.f,     
        0.5f,  0.5f, -0.5f,       0.f,  1.f,  0.f,       2.f, 0.f,     
        0.5f,  0.5f,  0.5f,       0.f,  1.f,  0.f,       2.f, 1.f,     
    };

    return cubeVertices;
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