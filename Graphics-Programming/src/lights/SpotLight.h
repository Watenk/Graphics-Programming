#pragma once

#include "Phong.h"
#include "Attenuation.h"

struct SpotLight{
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff; // Radius
    float outerCutOff; // Soft edges radius
    Attenuation attenuation;
    Phong phong;

    SpotLight(glm::vec3 position = glm::vec3(0.0f), glm::vec3 direction = glm::vec3(0.0f), float cutOff = 10.0f, float outerCutoff = 10.0f) 
             : position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff) {}
};