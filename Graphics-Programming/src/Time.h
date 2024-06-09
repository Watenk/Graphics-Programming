#pragma once

namespace Watenk{
class Time{

public:
    ~Time();

    void update();
    float getDeltaTime();
    float getLastFrame();

private:
    float deltaTime;
    float lastFrame;
};
}