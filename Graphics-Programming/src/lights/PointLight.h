#pragma once

#include "Phong.h"
#include "Attenuation.h"

struct PointLight{
    int index;
    glm::vec3 position;
    glm::vec3 color;
    Attenuation attenuation;
    Phong phong;

    PointLight(glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f)) : position(position), color(color) {}
};