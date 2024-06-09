#pragma once

#include "Inputs.h"

#include <vector>
#include <functional>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>

class InputHandler{

public:
    InputHandler(GLFWwindow* window);
    void update(GLFWwindow* window);
    void addKeyCallBack(EInputs input, std::function<void()> callback);
    void addMouseCallback(std::function<void(glm::vec2)> callback);

private:
    std::unordered_map<EInputs, std::function<void()>> keyCallbacks;
    std::vector<std::function<void(glm::vec2 mousePos)>> mouseCallbacks;
    glm::vec2 previousMousePos;
    GLFWwindow* window;

    void executeKeyCallback(EInputs input);
    void executeMouseCallback();
    glm::vec2 getMousePos() const;
};