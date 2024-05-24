#include "PlayerController.h"

#include <iostream>

PlayerController::PlayerController(InputHandler &input, Watenk::Time &watenkTime) : watenkTime(watenkTime){
    input.addInputCallBack(EInputs::forwards, [this](){ this->onForwards(); });
    input.addInputCallBack(EInputs::backwards, [this](){ this->onBackwards(); });
    input.addInputCallBack(EInputs::right, [this](){ this->onRight(); });
    input.addInputCallBack(EInputs::left, [this](){ this->onLeft(); });
    input.addInputCallBack(EInputs::up, [this](){ this->onUp(); });
    input.addInputCallBack(EInputs::down, [this](){ this->onDown(); });
    input.addInputCallBack(EInputs::boost, [this](){ this->onBoost(); });
}

void PlayerController::onForwards(){
    cam.transform.move(cam.transform.getFront() * watenkTime.getDeltaTime());
}

void PlayerController::onBackwards(){
    cam.transform.move(cam.transform.getFront() * -1.0f * watenkTime.getDeltaTime());
}

void PlayerController::onRight(){
    cam.transform.move(cam.transform.getRight() * watenkTime.getDeltaTime());
}

void PlayerController::onLeft(){
    cam.transform.move(cam.transform.getRight() * -1.0f * watenkTime.getDeltaTime());
}

void PlayerController::onUp(){
    cam.transform.move(cam.transform.getUp() * watenkTime.getDeltaTime());
}

void PlayerController::onDown(){
    cam.transform.move(cam.transform.getUp() * -1.0f * watenkTime.getDeltaTime());
}

void PlayerController::onBoost(){
}