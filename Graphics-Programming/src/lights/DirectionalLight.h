#pragma once

#include "Phong.h"

struct DirectionalLight{
    glm::vec3 direction;
    Phong phong;

    DirectionalLight(Phong phong = Phong{}, glm::vec3 direction = glm::vec3(1.2f, 1.0f, 2.0f)) : direction(direction) {}
};