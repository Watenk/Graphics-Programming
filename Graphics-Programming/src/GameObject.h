#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"

class GameObject{

public:
    Mesh mesh;
    Shader shader;
    std::vector<Texture2D> textures;

    GameObject(Mesh mesh, Shader shader, std::vector<Texture2D> textures);
    ~GameObject();
    void bind(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

private:

};