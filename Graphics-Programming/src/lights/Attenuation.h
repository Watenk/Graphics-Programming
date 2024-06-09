#pragma once

struct Attenuation{
    float constant;
    float linear;
    float quadratic;

    Attenuation(float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f) : constant(constant), linear(linear), quadratic(quadratic) {}
};
