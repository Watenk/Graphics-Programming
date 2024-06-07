#pragma once

#include "../GameObject.h"

class Component{
public:
    GameObject* gameObject;

    virtual void Init() = 0;
};