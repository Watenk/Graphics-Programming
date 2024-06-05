#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"

class Model{

public:
    Transform transform;
    Mesh* mesh;
    Shader* shader;

    Model(Mesh* mesh, Shader* shader, Camera* cam);
    ~Model();

    void draw() const;

private:
    Camera* cam;

    void bind() const;
    void unBind() const;
};