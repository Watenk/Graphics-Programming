#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Forward Declaration
int init(GLFWwindow* &window, const char* windowName);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);
void createTriangle();
void createShaders();

int main(){

    GLFWwindow* window;
    int res = init(window, "Graphics Programming");
    if (res != 0) return res;

    createTriangle();
    createShaders();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
        processInput(window);
        glfwPollEvents(); // Windows Window Events



        glfwSwapBuffers(window);
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

void createTriangle(){

}

void createShaders(){

}