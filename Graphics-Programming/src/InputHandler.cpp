#include "InputHandler.h"

void InputHandler::update(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) executeCallback(EInputs::forwards);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) executeCallback(EInputs::backwards);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) executeCallback(EInputs::left);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) executeCallback(EInputs::right);
}

void InputHandler::addInputCallBack(EInputs input, std::function<void()> callback){
    inputDict[input] = callback;
}

void InputHandler::executeCallback(EInputs input){
    auto it = inputDict.find(input);
    if (it == inputDict.end()) return;

    std::function<void()> callback = inputDict.at(input);
    callback();
}