#include "PlayerController.h"

#include <iostream>

PlayerController::PlayerController(InputHandler* &input, Watenk::Time* &watenkTime, Camera* &cam, float speed, float mouseSensitivity) 
                                    : watenkTime(watenkTime), cam(cam), speed(speed), mouseSensitivity(mouseSensitivity){

    input->addKeyCallBack(EInputs::forwards, [this](){ this->onForwards(); });
    input->addKeyCallBack(EInputs::backwards, [this](){ this->onBackwards(); });
    input->addKeyCallBack(EInputs::right, [this](){ this->onRight(); });
    input->addKeyCallBack(EInputs::left, [this](){ this->onLeft(); });
    input->addKeyCallBack(EInputs::up, [this](){ this->onUp(); });
    input->addKeyCallBack(EInputs::down, [this](){ this->onDown(); });
    input->addKeyCallBack(EInputs::boost, [this](){ this->onBoost(); });
    input->addMouseCallback([this](glm::vec2 mousePos){ this->onMouse(mousePos) ;});
}

PlayerController::~PlayerController(){
    delete(cam);
}

void PlayerController::onForwards(){
    cam->transform.move(cam->transform.getFront() * speed * watenkTime->getDeltaTime());
}

void PlayerController::onBackwards(){
    cam->transform.move(cam->transform.getFront() * speed * -1.0f * watenkTime->getDeltaTime());
}

void PlayerController::onRight(){
    cam->transform.move(cam->transform.getRight() * speed * watenkTime->getDeltaTime());
}

void PlayerController::onLeft(){
    cam->transform.move(cam->transform.getRight() * speed * -1.0f * watenkTime->getDeltaTime());
}

void PlayerController::onUp(){
    cam->transform.move(cam->transform.getUp() * speed * watenkTime->getDeltaTime());
}

void PlayerController::onDown(){
    cam->transform.move(cam->transform.getUp() * speed * -1.0f * watenkTime->getDeltaTime());
}

void PlayerController::onBoost() {}

void PlayerController::onMouse(glm::vec2 mousePos){
    // Pitch = y = up down ------ yaw = z = left right
    float mouseDeltaX = (mousePos.x - lastMousePos.x) * mouseSensitivity;
    float mouseDeltaY = (lastMousePos.y - mousePos.y) * mouseSensitivity;

    float yRotation = glm::clamp(cam->transform.getEuler().y + mouseDeltaY, -89.0f, 89.0f);
    float zRotation = cam->transform.getEuler().z + mouseDeltaX;

    cam->transform.setRotation(glm::vec3(0.0f, yRotation, zRotation));

    lastMousePos = mousePos;
}