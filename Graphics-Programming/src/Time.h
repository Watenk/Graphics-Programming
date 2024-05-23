#pragma once

#include "Interfaces/IUpdateable.h"

namespace Watenk{
class Time : public IUpdateable{

public:
    void update() override;
    float getDeltaTime();
    float getLastFrame();

private:
    float deltaTime;
    float lastFrame;
};
}