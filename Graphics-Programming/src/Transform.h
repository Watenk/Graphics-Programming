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
    glm::vec3 getUp();
    glm::vec3 getFront();
    glm::vec3 getRight();
    void setPos(glm::vec3);
    void setScale(glm::vec3);
    void setRotation(glm::quat rotation);
    void setRotation(glm::vec3 rotation);

    void move(glm::vec3);
    void rotate(glm::vec3);
    void scale(glm::vec3);
    void print();

private:
    glm::mat4 transformMatrix;
};