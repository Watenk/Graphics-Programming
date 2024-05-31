#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"

struct PhongLight{
    glm::vec3 ambient;    
    glm::vec3 diffuse;    
    glm::vec3 specular;

    PhongLight(glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f)) : ambient(ambient), diffuse(diffuse), specular(specular) {}
};

struct DirectionalLight{
    glm::vec3 direction;

    PhongLight phong;

    DirectionalLight(PhongLight phong = PhongLight{}, glm::vec3 direction = glm::vec3(1.2f, 1.0f, 2.0f)) : direction(direction) {}
};

struct PointLight{
    int index;
    glm::vec3 position;

    PhongLight phong;

    // Attenutation
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    int index;
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    PhongLight phong;

    // Attenutation
    float constant;
    float linear;
    float quadratic;
};

class Lights{

public:
    Lights(DirectionalLight directionalLight = DirectionalLight{});

    DirectionalLight getDirectionalLight();
    int getPointLightSize();
    //int getSpotLightSize();

    void addShader(Shader* shader);
    void setDirectionalLight(DirectionalLight newDirectionalLight);
    void addPointLight(PointLight pointLight);
    //void addSpotLight(SpotLight spotLight);
    void removePointLight(PointLight pointLight);
    void removeSpotLight(SpotLight spotLight);

private:
    DirectionalLight directionalLight;

    std::vector<PointLight> pointLights;
    //std::vector<SpotLight> spotLights;
    std::vector<Shader*> shaders;

    void updateShaderDirectional(Shader* shader);
    void updateShaderPoint(Shader* shader, PointLight light);
    //void updateShaderSpot(Shader* shader, SpotLight light);
};