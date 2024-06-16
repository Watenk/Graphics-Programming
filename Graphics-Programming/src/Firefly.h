#pragma once

#include "GameObject.h"
#include "lights/PointLight.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

class Firefly{

public:
    GameObject* gameObject;
    PointLight light;
    glm::vec3 centerPoint = glm::vec3(0.0f); 
    float radius = 5.0f; 
    float movementSpeed = 100.0f;

    Firefly(Camera* cam);
    void update(float deltaTime);

private:
    float randomFloat(float min, float max);
};