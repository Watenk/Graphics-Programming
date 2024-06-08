#pragma once

#include "Phong.h"
#include "Attenuation.h"

struct PointLight{
    glm::vec3 position;
    Attenuation attenuation;
    Phong phong;
};