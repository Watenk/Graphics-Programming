#pragma once

#include <vector>

#include "Texture2D.h"

struct Material{
    Texture2D* diffuseTexture;
    Texture2D* specularTexture;

    float shininess;

    Material() : diffuseTexture(new Texture2D("res/textures/smile.png")), specularTexture(new Texture2D("res/textures/smile.png")) {}
};