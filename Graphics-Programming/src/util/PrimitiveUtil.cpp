#include "PrimitiveUtil.h"

#include <glad/glad.h>

Mesh* PrimitiveUtil::getCube(){
    return new Mesh(GL_STATIC_DRAW, getCubeVertices(), getCubeIndices());
}

std::vector<float> PrimitiveUtil::getCubeVertices(){
    std::vector<float> cubeVertices = {
    // positions           // normals         // tex coords    //tangents      //bitangents
    0.5f, -0.5f, -0.5f,    0.f, -1.f, 0.f,    1.f, 1.f,        -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
    0.5f, -0.5f, 0.5f,     0.f, -1.f, 0.f,    1.f, 0.f,        -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
    -0.5f, -0.5f, 0.5f,    0.f, -1.f, 0.f,    0.f, 0.f,        -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
    -0.5f, -0.5f, -.5f,    0.f, -1.f, 0.f,    0.f, 1.f,        -1.f, 0.f, 0.f,  0.f, 0.f, 1.f,

    0.5f, 0.5f, -0.5f,     1.f, 0.f, 0.f,     1.f, 1.f,       0.f, -1.f, 0.f,  0.f, 0.f, 1.f,
    0.5f, 0.5f, 0.5f,      1.f, 0.f, 0.f,     1.f, 0.f,       0.f, -1.f, 0.f,  0.f, 0.f, 1.f,

    0.5f, 0.5f, 0.5f,      0.f, 0.f, 1.f,     1.f, 0.f,       1.f, 0.f, 0.f,  0.f, -1.f, 0.f,
    -0.5f, 0.5f, 0.5f,     0.f, 0.f, 1.f,     0.f, 0.f,       1.f, 0.f, 0.f,  0.f, -1.f, 0.f,

    -0.5f, 0.5f, 0.5f,    -1.f, 0.f, 0.f,     0.f, 0.f,       0.f, 1.f, 0.f,  0.f, 0.f, 1.f,
    -0.5f, 0.5f, -.5f,    -1.f, 0.f, 0.f,     0.f, 1.f,       0.f, 1.f, 0.f,  0.f, 0.f, 1.f,

    -0.5f, 0.5f, -.5f,    0.f, 0.f, -1.f,     0.f, 1.f,       1.f, 0.f, 0.f,  0.f, 1.f, 0.f,
    0.5f, 0.5f, -0.5f,    0.f, 0.f, -1.f,     1.f, 1.f,       1.f, 0.f, 0.f,  0.f, 1.f, 0.f,

    -0.5f, 0.5f, -.5f,     0.f, 1.f, 0.f,     1.f, 1.f,       1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
    -0.5f, 0.5f, 0.5f,     0.f, 1.f, 0.f,     1.f, 0.f,       1.f, 0.f, 0.f,  0.f, 0.f, 1.f,

    0.5f, -0.5f, 0.5f,     0.f, 0.f, 1.f,     1.f, 1.f,       1.f, 0.f, 0.f,  0.f, -1.f, 0.f,
    -0.5f, -0.5f, 0.5f,    0.f, 0.f, 1.f,     0.f, 1.f,       1.f, 0.f, 0.f,  0.f, -1.f, 0.f,

    -0.5f, -0.5f, 0.5f,    -1.f, 0.f, 0.f,    1.f, 0.f,        0.f, 1.f, 0.f,  0.f, 0.f, 1.f,
    -0.5f, -0.5f, -.5f,    -1.f, 0.f, 0.f,    1.f, 1.f,        0.f, 1.f, 0.f,  0.f, 0.f, 1.f,

    -0.5f, -0.5f, -.5f,    0.f, 0.f, -1.f,    0.f, 0.f,        1.f, 0.f, 0.f,  0.f, 1.f, 0.f,
    0.5f, -0.5f, -0.5f,    0.f, 0.f, -1.f,    1.f, 0.f,        1.f, 0.f, 0.f,  0.f, 1.f, 0.f,

    0.5f, -0.5f, -0.5f,    1.f, 0.f, 0.f,     0.f, 1.f,       0.f, -1.f, 0.f,  0.f, 0.f, 1.f,
    0.5f, -0.5f, 0.5f,     1.f, 0.f, 0.f,     0.f, 0.f,       0.f, -1.f, 0.f,  0.f, 0.f, 1.f,

    0.5f, 0.5f, -0.5f,     0.f, 1.f, 0.f,     0.f, 1.f,       1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
    0.5f, 0.5f, 0.5f,      0.f, 1.f, 0.f,     0.f, 0.f,       1.f, 0.f, 0.f,  0.f, 0.f, 1.f   
    };

    return cubeVertices;
}

std::vector<unsigned int> PrimitiveUtil::getCubeIndices(){
    std::vector<unsigned int> cubeIndices = {
        // Down
        0, 1, 2,      // first triangle
        0, 2, 3,      // second triangle
        // Back
        14, 6, 7,     // first triangle
        14, 7, 15,    // second triangle
        // Right
        20, 4, 5,     // first triangle
        20, 5, 21,    // second triangle
        // Left
        16, 8, 9,     // first triangle
        16, 9, 17,    // second triangle
        // Front
        18, 10, 11,   // first triangle
        18, 11, 19,   // second triangle
        // Up
        22, 12, 13,   // first triangle
        22, 13, 23,   // second triangle
    };

    return cubeIndices;
}