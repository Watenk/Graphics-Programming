#pragma once

#include "InputHandler.h"
#include "Camera.h"
#include "Time.h"

class PlayerController{

public:
    PlayerController(InputHandler &input, Watenk::Time &watenkTime);
    Camera cam;

private:
    Watenk::Time& watenkTime;

    void onForwards();
    void onBackwards();
    void onRight();
    void onLeft();
    void onUp();
    void onDown();
    void onBoost();
};