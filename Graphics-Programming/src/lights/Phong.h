#pragma once

#include "glm/glm.hpp"

/* Values must be normalized */
struct Phong{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Phong(glm::vec3 ambient = glm::vec3(0.2f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f)) : ambient(ambient), diffuse(diffuse), specular(specular) {}
};