#include "Time.h"

#include <GLFW/glfw3.h>

namespace Watenk{

Time::~Time() {}

void Time::update(){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;  
}

float Time::getDeltaTime(){
    return deltaTime;
}

float Time::getLastFrame(){
    return lastFrame;
}
}