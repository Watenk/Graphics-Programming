#pragma once

#include "Mesh.h"
#include "Material.h"

class GameObject{
public:
    Transform transform;
    Mesh* mesh;
    Shader* shader;
    Material* material;

    GameObject(Mesh* mesh, Shader* shader, Material* material, Camera* cam);
    void draw() const;

private:
    Camera* cam;
};