#pragma once

struct Attenuation{
    float constant;
    float linear;
    float quadratic;

    Attenuation(float constant = 1.0f, float linear = 0.022f, float quadratic = 0.0019f) : constant(constant), linear(linear), quadratic(quadratic) {}
};
