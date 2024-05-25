#include "Transform.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation) : position(POSITION), size(SIZE), rotation(ROTATION) {}

glm::mat4 Transform::getModelMatrix() const{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix *= glm::mat4_cast(rotation);
    modelMatrix = glm::scale(modelMatrix, size);
    return modelMatrix;
}

void Transform::printModelMatrix() const{
    glm::mat4 modelMatrix = getModelMatrix();

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            std::cout << modelMatrix[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

glm::vec3 Transform::getFront() const{
    glm::vec3 eulerDegrees = getEuler();
    glm::vec3 front;  
    front.x = cos(glm::radians(eulerDegrees.z)) * cos(glm::radians(eulerDegrees.y));
    front.y = sin(glm::radians(eulerDegrees.y));
    front.z = sin(glm::radians(eulerDegrees.z)) * cos(glm::radians(eulerDegrees.y));
    front = glm::normalize(front);
    return front;
}

glm::vec3 Transform::getRight() const{
    glm::vec3 worldUp = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::normalize(glm::cross(getFront(), worldUp));
    return right;
}

glm::vec3 Transform::getUp() const{
    glm::vec3 up = glm::normalize(glm::cross(getRight(), getFront()));
    return up;
}

glm::vec3 Transform::getEuler() const{
    return glm::degrees(glm::eulerAngles(rotation));
}

void Transform::setEuler(const glm::vec3& eulerDegrees){
    rotation = glm::quat(glm::radians(eulerDegrees));
}

void Transform::move(const glm::vec3& moveAmount){
    position += moveAmount;
}

void Transform::scale(const glm::vec3& scaleAmount){
    size += scaleAmount;
}

void Transform::rotate(const glm::vec3& rotateAmount){
    glm::vec3 newRotation = getEuler() + rotateAmount;
    setEuler(newRotation);
}