#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Forward Declaration
int init(GLFWwindow* &window, const char* windowName);
std::string parse(const std::string& filepath);
unsigned int compileShader(unsigned int type, const std::string& source);
unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);


int main(){

    /* GLFW Setup */
    GLFWwindow* window;
    int initCode = init(window, "Graphics Programming");
    if (initCode != 0) return initCode;

    /* Shaders */
    std::string basicVertexShaderString = parse("res/shaders/basic/basic.vertex");
    std::string basicFragmentShaderString = parse("res/shaders/basic/basic.fragment");

    unsigned int basicVertexShader = compileShader(GL_VERTEX_SHADER, basicVertexShaderString);
    unsigned int basicFragmentShader = compileShader(GL_FRAGMENT_SHADER, basicFragmentShaderString);

    unsigned int basicShaderProgram = createShaderProgram(basicVertexShader, basicFragmentShader);

    /* Vertex Data, VAO, VBO, EBO and Vertex Attributes */
    /* Vertex Data */
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    unsigned int VAO, VBO, EBO;

    /* Generate buffers */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* VAO */
    glBindVertexArray(VAO);

    /* VBO */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* EBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Vertex Attributes */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* Cleanup */
    /* note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind */
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Clears the VBO

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Clears the EBO

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); // Clears the VAO

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
        processInput(window);
        
        // Draw
        glUseProgram(basicShaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents(); // Windows Window Events
    }

    /* Cleanup */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(basicShaderProgram);

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

/* Reads the contents of a file
    @param filePath The path the text resides
    @return The contents of the file
 */
std::string parse(const std::string& filepath){
    std::ifstream stream(filepath);
    if (!stream.is_open()) {
        std::cerr << "Error: Failed to open file " << filepath << std::endl;
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current working directory: " << currentPath << std::endl;
    }

    std::stringstream ss;
    std::string line;
    while (getline(stream, line)){
        ss << line << '\n';
    }

    stream.close();
    return ss.str();
}

/* Compiles a GLSL string to a shader
    @param type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    @returns A compiled shader
*/
unsigned int compileShader(unsigned int type, const std::string& source){
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // Error handling
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader Compilation Failed\n" << infoLog << std::endl;
    }

    return shader;
}

/* Creates a shader program and links the vertex and fragment Shader to it. The shaders will be deleted afterwards
    @return A shaderprogram
*/
unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader){
    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Error handling
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    // Check for validation errors
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader Program Validation Failed: " << infoLog << std::endl;
    }

    // The shaders are attached to the program so they can be deleted
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}