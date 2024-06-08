#pragma once

#include "../Texture2D.h"
#include "../Mesh.h"
#include "../GameObject.h"

class TerrainUtil{

public:
    static GameObject* generateTerrain(Texture2D* heightmap, float heightScale, float xzScale, Shader* shader, Material* material, Camera* cam);
};