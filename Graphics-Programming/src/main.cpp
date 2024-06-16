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
#include "lights/lightManager.h"
#include "GameObject.h"
#include "Firefly.h"
#include "util/ModelUtil.h"
#include "util/TerrainUtil.h"
#include "util/PrimitiveUtil.h"

const char* WINDOWNAME = "Unreal Engine 6";
const unsigned int WINDOWWIDTH = 1280;
const unsigned int WINDOWHEIGHT = 720;
const int FIREFLYAMOUNT = 1;

/* Forward Declaration */
int initGLFW(GLFWwindow* &window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void printVec3(glm::vec3 vec3);
void DrawGameObjects(std::vector<GameObject*> gameObjects);
void placeGameObjects(std::vector<GameObject*> gameObjects, glm::vec3 pos);
void orientateGameObjects(std::vector<GameObject*> gameObjects, glm::vec3 rotation);
void sizeGameObjects(std::vector<GameObject*> gameObjects, glm::vec3 size);

/* Managers */
GLFWwindow* window;
InputHandler* input;
Watenk::Time* watenkTime;
PlayerController* player;
Camera* cam;
LightManager* lightManager;

/* Scene */
std::vector<Firefly> fireflys;

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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /* Managers */
    input = new InputHandler(window);
    watenkTime = new Watenk::Time();
    cam = new Camera(WINDOWWIDTH, WINDOWHEIGHT, POSITION, 90.0f, 0.1f, 5000.0f);
    player = new PlayerController(input, watenkTime, cam, 5.0f);
    lightManager = new LightManager();

    /* Shaders */
    Shader* defaultShader = new Shader();
    Shader* skyboxShader = new Shader("skybox");
    Shader* terrainShader = new Shader("terrain");

    /* Materials */
    Material* emptyMaterial = new Material();

    Material* skyBoxMaterial = new Material();
    skyBoxMaterial->shininess = 64.0f;

    Material* containerMaterial = new Material();
    containerMaterial->diffuseTexture = new Texture2D("res/textures/container.png");
    containerMaterial->specularTexture = new Texture2D("res/textures/containerSpecular.png");
    containerMaterial->normalTexture = new Texture2D("res/textures/containerNormal.png");
    containerMaterial->shininess = 64.0f;

    Material* terrainMaterial = new Material();
    terrainMaterial->diffuseTexture = new Texture2D("res/textures/terrain/heightmap.png");
    terrainMaterial->specularTexture = new Texture2D("res/textures/terrain/heightmap.png");
    terrainMaterial->normalTexture = new Texture2D("res/textures/terrain/heightmapNormal.png");
    terrainMaterial->extraTextures.push_back(new Texture2D("res/textures/terrain/dirt.jpg"));
    terrainMaterial->extraTextures.push_back(new Texture2D("res/textures/terrain/sand.jpg"));
    terrainMaterial->extraTextures.push_back(new Texture2D("res/textures/terrain/grass.png"));
    terrainMaterial->extraTextures.push_back(new Texture2D("res/textures/terrain/rock.jpg"));
    terrainMaterial->extraTextures.push_back(new Texture2D("res/textures/terrain/snow.jpg"));
    terrainMaterial->shininess = 1.0f;

    /* Manual Meshes */
    Mesh* cubeMesh = PrimitiveUtil::getCube();

    /* GameObjects */
    GameObject* container = new GameObject(cubeMesh, defaultShader, containerMaterial, cam);
    GameObject* skyBox = new GameObject(cubeMesh, skyboxShader, skyBoxMaterial, cam);
    GameObject* terrain = TerrainUtil::generateTerrain(new Texture2D("res/textures/terrain/heightmap.png"), 50.0f, 1.0f, terrainShader, terrainMaterial, cam);
    //std::vector<GameObject*> backpack = ModelUtil::loadModel(GL_STATIC_DRAW, "res/models/backpack/backpack.obj", defaultShader, cam, 64.0f);

    /* Scene */
    skyBox->transform.setParent(cam->transform);
    container->transform.setPosition(glm::vec3(1.0f));
    for (int i = 0; i < FIREFLYAMOUNT; i++){
        fireflys.push_back(Firefly(cam));
    }
    
    /* Lights */
    DirectionalLight dirLight = lightManager->getDirectionalLight();
    dirLight.phong.ambient = glm::vec3(0.05f);
    dirLight.phong.diffuse = glm::vec3(0.2f);
    lightManager->setDirectionalLight(dirLight);
    lightManager->addShader(defaultShader);
    lightManager->addShader(terrainShader);
    for (Firefly fly : fireflys){
        lightManager->addPointLight(fly.light);
    }
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Managers */
        input->update(window);
        watenkTime->update();

        DirectionalLight dirLight = lightManager->getDirectionalLight();
        dirLight.direction = glm::normalize(glm::vec3(glm::sin(glfwGetTime()), 0.5f, glm::cos(glfwGetTime())));
        lightManager->setDirectionalLight(dirLight);

        /* Uniform Updates */
        defaultShader->setVec3("viewPos", cam->transform->getPosition());
        skyboxShader->setVec3("viewPos", cam->transform->getPosition());
        skyboxShader->setVec3("lightDirection", lightManager->getDirectionalLight().direction);
        terrainShader->setVec3("viewPos", cam->transform->getPosition());

        /* GameObject Updates */
        for (Firefly fly : fireflys){
            fly.update(watenkTime->getDeltaTime());
        }

        /* Buffers */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw ----------------
        
	    glDisable(GL_CULL_FACE);
	    glDisable(GL_DEPTH_TEST);
        skyBox->draw();
        glEnable(GL_CULL_FACE);
	    glEnable(GL_DEPTH_TEST);

        container->draw();
        terrain->draw();
        for (Firefly fly : fireflys){
            fly.gameObject->draw();
        }

        // Draw end -------------

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

void DrawGameObjects(std::vector<GameObject*> gameObjects){
    for (GameObject* gameObject : gameObjects){
        gameObject->draw();
    }
}

void placeGameObjects(std::vector<GameObject*> gameObjects, glm::vec3 pos){
    for (GameObject* gameObject : gameObjects){
        gameObject->transform.setPosition(pos);
    }
}

void orientateGameObjects(std::vector<GameObject*> gameObjects, glm::vec3 rotation){
    for (GameObject* gameObject : gameObjects){
        gameObject->transform.setRotation(rotation);
    }
}

void sizeGameObjects(std::vector<GameObject*> gameObjects, glm::vec3 size){
    for (GameObject* gameObject : gameObjects){
        gameObject->transform.setSize(size);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

void printVec3(glm::vec3 vec3){
    std::cout << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")" << std::endl;
}