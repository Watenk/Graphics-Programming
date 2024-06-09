#include "Camera.h"


Camera::Camera(unsigned int windowWidth, unsigned int windowHeight, glm::vec3 pos, float fov, float nearPlaneCutoff, float farPlaneCutoff) 
               : windowWidth(windowWidth), windowHeight(windowHeight), fov(fov), nearPlaneCutoff(nearPlaneCutoff), farPlaneCutoff(farPlaneCutoff){
    transform = new Transform();
    transform->setRotation(glm::vec3(0, 0, -90));
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(transform->getPosition(), transform->getPosition() + transform->getFront(), transform->getUp());
}

glm::mat4 Camera::getProjectionMatrix() const{
    return glm::perspective(glm::radians(fov), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), nearPlaneCutoff, farPlaneCutoff);
}