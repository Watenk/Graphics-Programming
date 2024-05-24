#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

class Camera{

public:
    Transform transform;

    // Camera options
    float speed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f));
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};