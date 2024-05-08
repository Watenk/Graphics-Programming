#pragma once

#include "Shader.h"

class Mesh{
public:
    
    /**
     * Mesh with only float attributes
     * @param usage is the usage method openGL uses to draw (GL_STATIC_DRAW, GL_DYNAMIC_DRAW or GL_STREAM_DRAW)
     * @param vertexData the array of vertexData (position, color, UV, etc...)
     * @param vertexDataSize sizeof(vertexData)
     * @param attributeAmount sizeof(attributeLenghts) / sizeof(int) amount of attributes in the vertices
     * @param attributeLenghts the size of each vertex attribute (pos has lenght of 3 (x, y, z))
     * @param indicesAmount sizeof(indices) / sizeof(unsigned int) the amount of indices
     * @param indices the order the vertices are drawn
    */
    Mesh(const int usage, const float vertexData[], const int vertexDataSize, const int attributeAmount, const int attributeLenghts[], const int indicesAmount, const unsigned int indices[]); 
    ~Mesh();
    
    /* Binds this VAO as the current VAO of OpenGL */
    void bind() const;

    const int getIndicesAmount() const;

private:
    unsigned int VAO, VBO, EBO;
    int indicesAmount;
};