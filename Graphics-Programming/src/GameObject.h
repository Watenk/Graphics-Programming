#pragma once

#include <vector>
#include <unordered_map>

#include "Transform.h"
#include "Interfaces/Component.h"

class GameObject{

public:

    GameObject();

    template<typename T> T* getComponent();
    template<typename T> void addComponent(const T* component);

private:
    std::unordered_map<std::type_info, Component*> components;
};