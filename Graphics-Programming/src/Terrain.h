#pragma once

#include "Texture2D.h"
#include "Mesh.h"

const float XZSCALE = 1;
const float HEIGHTSCALE = 0;

class Terrain{

public:
    Texture2D* heightmap;
    Mesh* mesh;

    Terrain(Texture2D* heightMap, float heightScale = HEIGHTSCALE, float xzScale = XZSCALE);

private:

};