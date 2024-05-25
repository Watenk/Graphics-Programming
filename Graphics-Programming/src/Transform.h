#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 SIZE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::quat ROTATION = glm::quat();

class Transform{

public:
    Transform(glm::vec3 position = POSITION, glm::vec3 scale = SIZE, glm::quat rotation = ROTATION);

    /* Model Matrix */
    glm::mat4 getModelMatrix() const;
    void printModelMatrix() const;

    /* Directions */
    glm::vec3 getFront() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    /* Euler */
    glm::vec3 getEuler() const;
    void setEuler(const glm::vec3& eulerDegrees);

    /* Transform interactions */
    void move(const glm::vec3& moveAmount);
    void scale(const glm::vec3& scaleAmount);
    void rotate(const glm::vec3& rotateAmount);

    glm::vec3 position;
    glm::vec3 size;
    glm::quat rotation;
};