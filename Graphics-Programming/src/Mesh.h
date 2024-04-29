#pragma once

#include "Shader.h"

class Mesh{
public:
    
    /**
     * Mesh with only float attributes
     * @param usage is the usage method openGL uses to draw (GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW)
     * @param vertexData the array of vertexData (position, color, UV, etc...)
     * @param vertexData sizeof(vertexData)
     * @param attributeAmount amount of attributes in the vertices
     * @param attributeLenghts the size of each vertex attribute (pos has lenght of 3 (x, y, z))
     * @param indices the order the vertices are drawn
    */
    Mesh(const int usage, const float vertexData[], const int vertexDataSize, const int attributeAmount, const int attributeLenghts[], const unsigned int indices[], const int indicesAmount); 
    ~Mesh();
    
    /* Binds this VAO as the current VAO of OpenGL */
    void bind() const;

    const int getIndicesAmount() const;

private:
    unsigned int VAO, VBO, EBO;
    int indicesAmount;
};