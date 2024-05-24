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

glm::vec3 Transform::getFront(){
    glm::vec3 eulerAngles = getEuler();
    glm::vec3 front;  
    front.x = cos(glm::radians(eulerAngles.z)) * cos(glm::radians(eulerAngles.y));
    front.y = sin(glm::radians(eulerAngles.x)) * sin(glm::radians(eulerAngles.y));
    front.z = sin(glm::radians(eulerAngles.z)) * cos(glm::radians(eulerAngles.y));
    front = glm::normalize(front);
    return front;
}

glm::vec3 Transform::getRight(){
    glm::vec3 worldUp = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::normalize(glm::cross(getFront(), worldUp));
    return right;
}

glm::vec3 Transform::getUp(){
    glm::vec3 up = glm::normalize(glm::cross(getRight(), getFront()));
    return up;
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

void Transform::move(glm::vec3 moveAmount){
    glm::vec3 currentPos = getPos();
    glm::vec3 newPos = glm::vec3(currentPos.x + moveAmount.x, currentPos.y + moveAmount.y, currentPos.z + moveAmount.z);
    setPos(newPos);
}

void Transform::rotate(glm::vec3 rotateAmount){
    glm::vec3 currentEuler = getEuler();
    glm::vec3 newEuler = glm::vec3(currentEuler.x + rotateAmount.x, currentEuler.y + rotateAmount.y, currentEuler.z + rotateAmount.z);
    setRotation(newEuler);
}

void Transform::scale(glm::vec3 scaleAmount){
    glm::vec3 currentScale = getScale();
    glm::vec3 newScale = glm::vec3(currentScale.x + scaleAmount.x, currentScale.y + scaleAmount.y, currentScale.z + scaleAmount.z);
    setScale(newScale);
}

void Transform::print(){
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            std::cout << transformMatrix[y][x] << " ";
        }
        std::cout << std::endl;
    }
}