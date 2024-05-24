#include "Transform.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

Transform::Transform() : transformMatrix(glm::mat4(1.0f)) {}

glm::vec3 Transform::getPos(){
    glm::vec3 pos = glm::vec3(transformMatrix[3][0], transformMatrix[3][1], transformMatrix[3][2]);
    return pos;
}

glm::quat Transform::getRotation(){
    return glm::quat_cast(transformMatrix);
}

glm::vec3 Transform::getEuler(){
    return glm::degrees(glm::eulerAngles(glm::quat_cast(transformMatrix)));
}

glm::vec3 Transform::getScale(){
    glm::vec3 scale = glm::vec3(transformMatrix[0][0], transformMatrix[1][1], transformMatrix[2][2]);
    return scale;
}

void Transform::setPos(glm::vec3 pos){
    transformMatrix[3][0] = 0;
    transformMatrix[3][1] = 0;
    transformMatrix[3][2] = 0;
    transformMatrix = glm::translate(transformMatrix, pos);
}

void Transform::setScale(glm::vec3 scale){
    transformMatrix[0][0] = 0;
    transformMatrix[1][1] = 0;
    transformMatrix[2][2] = 0;
    transformMatrix = glm::scale(transformMatrix, scale);
}

void Transform::setRotation(glm::quat rotation){
    transformMatrix = transformMatrix * glm::mat4_cast(rotation);
}

void Transform::setRotation(glm::vec3 eulerRotation){
    transformMatrix = transformMatrix * glm::mat4_cast(glm::quat(glm::radians(eulerRotation)));
}

void Transform::print(){
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            std::cout << transformMatrix[y][x] << " ";
        }
        std::cout << std::endl;
    }
}