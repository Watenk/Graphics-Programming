#pragma once

#include <string>

class Shader{
public:
    /**
     * Takes the path of the vertex and fragment shader and parses, compiles and makes a shader program from it
     * @param shadersPath is the path of the dir that contains the shaders
     * @param shaderName is the name of the vertexShader and fragmentShader
    */
    Shader(const std::string& shadersPath, const std::string& shaderName);
    ~Shader();

    /* Binds this shader program as the current shader program of OpenGL */
    void bind() const;

    unsigned int getID() const;

private:
    unsigned int shaderProgramID;

    /**
     * Compiles a GLSL string to a shader
     * @param type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     * @returns A compiled shader
    */
    const unsigned int compileShader(const unsigned int type, const std::string& source);

    /**
     * Creates a shader program and links the vertex and fragment Shader to it. The shaders will be deleted afterwards
     * @return A shaderprogram
    */
    const unsigned int createShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader);
};