#pragma once

#include "Phong.h"
#include "Attenuation.h"

struct PointLight{
    int index;
    glm::vec3 position;
    glm::vec3 color;
    Attenuation attenuation;
    Phong phong;

    PointLight(glm::vec3 position = glm::vec3(1.0f)) : position(position) {}
};