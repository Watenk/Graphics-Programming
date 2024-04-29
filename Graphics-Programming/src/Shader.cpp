#include "Shader.h"

#include <glad/glad.h>
#include <iostream>

#include "util/FileUtil.h"

// Public

Shader::Shader(const std::string& shadersPath, const std::string& shaderName){
    // Shader Parseing
    std::string vertexString = FileUtil::parsePath(shadersPath + "/" + shaderName + ".vert");
    std::string fragmentString = FileUtil::parsePath(shadersPath + "/" + shaderName + ".frag");

    // Shader Compilation
    const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexString);
    const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentString);

    // Shader Program
    shaderProgramID = createShaderProgram(vertexShader, fragmentShader);
}

Shader::~Shader(){
    glDeleteProgram(shaderProgramID);
}

void Shader::bind() const{
    glUseProgram(shaderProgramID);
}

unsigned int Shader::getShaderProgramID() const{
    return shaderProgramID;
}

// Private

const unsigned int Shader::compileShader(const unsigned int type, const std::string& source){
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

const unsigned int Shader::createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader){
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