#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

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
    void setVec4(const char* name, const glm::vec4 data);
    void setVec3(const char* name, const glm::vec3 data);
    void setVec2(const char* name, const glm::vec2 data);
    void setFloat(const char* name, const float data);
    void setInt(const char* name, const int data);
    void setUInt(const char* name, unsigned int data);

    void setVec4Array(const char* name, std::vector<glm::vec4> data);
    void setVec3Array(const char* name, std::vector<glm::vec3> data);
    void setVec2Array(const char* name, std::vector<glm::vec2> data);
    void setFloatArray(const char* name, std::vector<float> data);
    void setIntArray(const char* name, std::vector<int> data);
    void setUIntArray(const char* name, std::vector<unsigned int> data);

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

    unsigned int getUniformLocation(const char* name);
};