#pragma once

#include "InputHandler.h"
#include "Camera.h"
#include "Time.h"

const float MOUSESENSITIVITY = 0.1f;
const float SPEED = 1.0f;

class PlayerController{

public:
    PlayerController(InputHandler* &input, Watenk::Time* &watenkTime, Camera* &cam, float speed = SPEED, float mouseSensitivity = MOUSESENSITIVITY);
    ~PlayerController();
    Camera* cam;

    float mouseSensitivity;
    float speed;

private:
    Watenk::Time* &watenkTime;
    glm::vec2 lastMousePos;

    void onForwards();
    void onBackwards();
    void onRight();
    void onLeft();
    void onUp();
    void onDown();
    void onBoost();
    void onMouse(glm::vec2 mousePos);
};