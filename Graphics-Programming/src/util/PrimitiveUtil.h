#pragma once

#include <vector>

#include "../Mesh.h"

class PrimitiveUtil{

public:
    static Mesh* getCube();

private:
    static std::vector<float> getCubeVertices();
    static std::vector<unsigned int> getCubeIndices();
};