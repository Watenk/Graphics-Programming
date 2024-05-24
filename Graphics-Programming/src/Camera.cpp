#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) 
    : up(up), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM){
    transform.setPos(pos);
}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(transform.getPos(), transform.getPos() + front, up);
}