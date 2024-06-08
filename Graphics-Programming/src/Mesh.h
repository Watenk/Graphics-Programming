#pragma once

#include "Shader.h"
#include "Texture2D.h"
#include "Material.h"

#include <vector>

const std::vector<int> ATTRIBUTES = {
    // Pos   // Normals   // Tex coords(UV)   // Tangents    // BiTangent
    3,       3,           2,                  3,             3
};

const std::vector<Texture2D*> TEXTURES = {};

class Mesh{
public:
    const std::vector<float> vertices;
    const std::vector<unsigned int> indices;

    Mesh(const int usage, const std::vector<float> vertices, const std::vector<unsigned int> indices, const std::vector<int> attributes = ATTRIBUTES); 
    ~Mesh();
    
    /* Draws this mesh */
    void draw(Transform transform, Shader* shader, Material* material, Camera* cam) const;

private:
    unsigned int VAO, VBO, EBO;
    ;

    /* Binds this VAO as the current VAO of OpenGL */
    void bind() const;
};