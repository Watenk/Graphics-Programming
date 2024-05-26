#pragma once

#include "Shader.h"

#include <vector>

class Mesh{
public:
    
    Mesh(const int usage, const std::vector<float> vertices, const std::vector<int> attributeLenghts, const std::vector<unsigned int> indices); 
    ~Mesh();
    
    /* Binds this VAO as the current VAO of OpenGL */
    void bind() const;

    const int getIndicesAmount() const;

private:
    unsigned int VAO, VBO, EBO;
    int indicesAmount;
};