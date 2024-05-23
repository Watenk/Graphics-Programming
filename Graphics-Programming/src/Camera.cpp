#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM){

}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(position, position + front, up);
}

void Camera::setSpeed(float newSpeed){
    speed = newSpeed;
}