#include "Transform.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation) : position(POSITION), size(SIZE), rotation(ROTATION) {}

Transform::Transform(Transform* parent, glm::vec3 position, glm::vec3 scale, glm::quat rotation) : parent(parent), position(POSITION), size(SIZE), rotation(ROTATION) {}

/* Model Matrix */
glm::mat4 Transform::getModelMatrix() const{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix *= glm::mat4_cast(rotation);
    modelMatrix = glm::scale(modelMatrix, size);
    return modelMatrix;
}

/* Directions */
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

/* Transform */
glm::vec3 Transform::getPosition() const{
    return position;
}

glm::vec3 Transform::getSize() const{
    return size;
}

glm::vec3 Transform::getEuler() const{
    return glm::degrees(glm::eulerAngles(rotation));
}

glm::quat Transform::getRotation() const{
    return rotation;
}

glm::vec3 Transform::getLocalPosition() const{
    return localPosition;
}

glm::vec3 Transform::getLocalSize() const{
    return localSize;
}

glm::quat Transform::getLocalRotation() const{
    return localRotation;
}

void Transform::setPosition(const glm::vec3 newPosition){
    position = newPosition;
    localPosition = parent->getPosition() - position;

    for (Transform* child : children){
        child->setPosition(position + child->getLocalPosition());
    }
}

void Transform::setSize(const glm::vec3 newSize){
    size = newSize;
    localSize = parent->getSize() - size;

    for (Transform* child : children){
        child->setSize(size + child->getLocalSize());
    }
}

void Transform::setRotation(const glm::quat newRotation){
    rotation = newRotation;
    localRotation = glm::conjugate(parent->getRotation()) * rotation;
    
    for (Transform* child : children){
        child->setRotation(rotation * child->getLocalRotation());
    }
}

void Transform::setRotation(const glm::vec3& eulerDegrees){
    setRotation(glm::quat(glm::radians(eulerDegrees)));
}

/* Transform interactions */
void Transform::move(const glm::vec3& moveAmount){
    setPosition(position += moveAmount);
}

void Transform::scale(const glm::vec3& scaleAmount){
    setSize(size += scaleAmount);
}

void Transform::rotate(const glm::vec3& rotateAmountEulerDegrees){
    setRotation(rotation *= glm::quat(glm::radians(rotateAmountEulerDegrees)));
}