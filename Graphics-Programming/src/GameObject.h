#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"

class GameObject{

public:
    Transform transform;
    Mesh* mesh;
    Shader* shader;
    std::vector<Texture2D*> textures;

    GameObject(Mesh* mesh, Shader* shader, std::vector<Texture2D*> textures, Camera* cam);
    ~GameObject();
    void draw() const;

private:
    Camera* cam;
    GameObject();

    void bind() const;
    void bindTextures() const;
};