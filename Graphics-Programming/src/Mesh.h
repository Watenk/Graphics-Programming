#pragma once

#include "Shader.h"
#include "Texture2D.h"

#include <vector>

class Mesh{
public:
    const std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D*> textures;

    Mesh(const int usage, const std::vector<float> vertices, const std::vector<unsigned int> indices, const std::vector<Texture2D*> textures, const std::vector<int> attributes, Shader* shader); 
    ~Mesh();
    
    /* Draws this mesh */
    void draw() const;
    void changeShader(Shader* _shader);

private:
    unsigned int VAO, VBO, EBO;
    Shader* shader;

    /* Binds this VAO as the current VAO of OpenGL */
    void bind() const;
    /* Binds to 0 */
    void unBind() const;
};