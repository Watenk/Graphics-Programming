#pragma once

#include <vector>

#include "Texture2D.h"

struct Material{
    Texture2D* diffuseTexture;
    Texture2D* specularTexture;
    Texture2D* normalTexture;

    std::vector<Texture2D*> extraTextures;

    float shininess;

    Material() : diffuseTexture(nullptr), specularTexture(nullptr), normalTexture(nullptr), shininess(0.0f) {}
};