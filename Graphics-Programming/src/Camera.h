#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

// Default values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera{

public:
    Transform transform;

    // Euler Angles
    float yaw;
    float pitch;

    // Camera options
    float speed;
    float mouseSensitivity;
    float zoom;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    glm::mat4 getViewMatrix();

private:
    // Camera Attributes
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;
};