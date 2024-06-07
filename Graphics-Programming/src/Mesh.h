#pragma once

#include "Shader.h"
#include "Texture2D.h"
#include"Interfaces/Component.h"

#include <vector>

const std::vector<int> ATTRIBUTES = {
    // Pos   // Normals   // Tex coords(UV)
    3,       3,           2,      
};

class Mesh : public Component{
public:
    Transform* transform;

    const std::vector<float> vertices;
    const std::vector<unsigned int> indices;
    const std::vector<Texture2D*> textures;

    Mesh(const int usage, const std::vector<float> vertices, const std::vector<unsigned int> indices, const std::vector<Texture2D*> textures, const Camera* cam, const std::vector<int> attributes = ATTRIBUTES); 
    ~Mesh();
    void Init() override;
    
    /* Draws this mesh */
    void draw(Shader* shader) const;

private:
    unsigned int VAO, VBO, EBO;
    const Camera* cam;

    /* Binds this VAO as the current VAO of OpenGL */
    void bind() const;
    void updateShaderUniforms(Shader* _shader) const;
};