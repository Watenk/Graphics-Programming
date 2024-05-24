#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform{

public:
    Transform();
    glm::vec3 getPos();
    glm::vec3 getScale();
    glm::quat getRotation();
    glm::vec3 getEuler();
    void setPos(glm::vec3);
    void setScale(glm::vec3);
    void setRotation(glm::quat rotation);
    void setRotation(glm::vec3 rotation);
    void print();

private:
    glm::mat4 transformMatrix;
};