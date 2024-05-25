#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Transform.h"

const float FOV = 45.0f;
const float NEARPLANECUTOFF = 0.1f;
const float FARPLANECUTOFF = 100.0f;

class Camera{

public:
    Transform transform;
    float fov;
    float nearPlaneCutoff;
    float farPlaneCutoff;

    Camera(unsigned int windowWidth, unsigned int windowHeight, glm::vec3 pos = POSITION, float fov = FOV, float nearPlaneCutoff = NEARPLANECUTOFF, float farPlaneCutoff = FARPLANECUTOFF);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    unsigned int windowWidth;
    unsigned int windowHeight;
};