#pragma once

#include "Phong.h"
#include "Attenuation.h"

struct SpotLight{
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;
    Attenuation attenuation;
    Phong phong;
};