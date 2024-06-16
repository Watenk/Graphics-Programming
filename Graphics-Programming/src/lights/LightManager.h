#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "../Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class LightManager{

public:
    LightManager(DirectionalLight directionalLight = DirectionalLight{});

    void update();

    DirectionalLight getDirectionalLight();
    int getPointLightAmount();
    //int getSpotLightSize();

    void addShader(Shader* shader);
    void setDirectionalLight(DirectionalLight newDirectionalLight);
    void addPointLight(PointLight* pointLight);
    //void addSpotLight(SpotLight spotLight);
    void removePointLight(PointLight* pointLight);
    //void removeSpotLight(SpotLight spotLight);

private:
    DirectionalLight directionalLight;

    std::vector<PointLight*> pointLights;
    //std::vector<SpotLight> spotLights;
    std::vector<Shader*> shaders;

    void updateShaderDirectional(Shader* shader);
    void updateShaderPoint(Shader* shader, PointLight* light);
    //void updateShaderSpot(Shader* shader, SpotLight light);
};