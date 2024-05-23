#pragma once

#include "Inputs.h"

#include <functional>
#include <GLFW/glfw3.h>
#include <map>

class InputHandler{

public:
    void update(GLFWwindow* window);
    void addInputCallBack(EInputs input, std::function<void()> callback);

private:
    std::unordered_map<EInputs, std::function<void()>> inputDict;

    void executeCallback(EInputs input);
};