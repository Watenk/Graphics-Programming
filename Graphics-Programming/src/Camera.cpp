#include "Camera.h"

Camera::Camera(glm::vec3 pos){
    transform.setPos(pos);
    transform.setRotation(glm::vec3(0, 0, -90));
}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(transform.getPos(), transform.getPos() + transform.getFront(), transform.getUp());
}

glm::mat4 Camera::getProjectionMatrix(){
    return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}