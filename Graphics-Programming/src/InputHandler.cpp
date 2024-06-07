#include "InputHandler.h"

InputHandler::InputHandler(GLFWwindow* window) : window(window), previousMousePos(glm::vec2(0.0f, 0.0f)) {}

void InputHandler::update(GLFWwindow* window){
    /* Keys */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) executeKeyCallback(EInputs::forwards);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) executeKeyCallback(EInputs::backwards);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) executeKeyCallback(EInputs::left);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) executeKeyCallback(EInputs::right);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) executeKeyCallback(EInputs::up);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) executeKeyCallback(EInputs::down);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) executeKeyCallback(EInputs::boostDown);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) executeKeyCallback(EInputs::boostUp);

    /* Mouse */
    executeMouseCallback();
}

void InputHandler::addKeyCallBack(EInputs input, std::function<void()> callback){
    keyCallbacks[input] = callback;
}

void InputHandler::addMouseCallback(std::function<void(glm::vec2 mousePos)> callback){
    mouseCallbacks.push_back(callback);
}

void InputHandler::executeKeyCallback(EInputs input){
    auto it = keyCallbacks.find(input);
    if (it == keyCallbacks.end()) return;

    std::function<void()> callback = keyCallbacks.at(input);
    callback();
}

void InputHandler::executeMouseCallback(){
    for (const auto& callback : mouseCallbacks) {
        callback(getMousePos());
    }
}

glm::vec2 InputHandler::getMousePos() const{
    glm::dvec2 mousePosDouble = glm::dvec2(0.0f, 0.0f);
    glfwGetCursorPos(window, &mousePosDouble.x, &mousePosDouble.y);
    glm::vec2 mousePos(mousePosDouble);
    return mousePos;
}