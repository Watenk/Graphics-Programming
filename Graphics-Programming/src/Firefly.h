#pragma once

#include "GameObject.h"
#include "lights/PointLight.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

class Firefly{

public:
    GameObject* gameObject;
    PointLight* light;
    glm::vec3 centerPoint;
    float radius = 5.0f; 
    float movementSpeed = 50.0f;

    Firefly(glm::vec3 centerPoint, glm::vec3 color, Shader* colorShader, Camera* cam);
    void update(float deltaTime);
};