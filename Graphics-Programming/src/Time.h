#pragma once

namespace Watenk{
class Time{

public:
    void update();
    float getDeltaTime();
    float getLastFrame();

private:
    float deltaTime;
    float lastFrame;
};
}