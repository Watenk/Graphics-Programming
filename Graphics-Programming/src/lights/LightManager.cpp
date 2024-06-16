#include "LightManager.h"

#include <iostream>
#include <algorithm>

LightManager::LightManager(DirectionalLight directionalLight) : directionalLight(directionalLight) {}

void LightManager::update(){
    for (Shader* shader : shaders){
        updateShaderDirectional(shader);

        for (PointLight* light : pointLights){
            updateShaderPoint(shader, light);
        }
    }
}

DirectionalLight LightManager::getDirectionalLight(){
    return directionalLight;
}

int LightManager::getPointLightAmount(){
    return pointLights.size();
}

// int Lights::getSpotLightSize(){
//     return spotLights.size();
// }

void LightManager::addShader(Shader* shader){
    shaders.push_back(shader);
    updateShaderDirectional(shader);

    for (PointLight* light : pointLights){
        updateShaderPoint(shader, light);
    }
    // for (SpotLight light : spotLights){
    //     updateShaderSpot(shader, light);
    // }
}

void LightManager::setDirectionalLight(DirectionalLight newDirectionalLight){
    directionalLight = newDirectionalLight;
    for (Shader* shader : shaders){
        updateShaderDirectional(shader);
    }
}

void LightManager::addPointLight(PointLight* pointLight){
    pointLight->index = pointLights.size();
    pointLights.push_back(pointLight);

    for (Shader* shader : shaders){
        shader->setInt("activePointLights", pointLights.size());
        updateShaderPoint(shader, pointLight);
    }
}

// void Lights::addSpotLight(SpotLight spotLight){
//     int index = freeSpotIndexes.front();
//     freeSpotIndexes.erase(freeSpotIndexes.begin());

//     spotLight.index = index;
//     spotLights.push_back(spotLight);
//     for (Shader* shader : shaders){
//         shader->setInt("activeSpotLights", 16 - freeSpotIndexes.size());
//         updateShaderSpot(shader, spotLight);
//     }
// }

void LightManager::removePointLight(PointLight* pointLight) {
    auto it = std::find_if(pointLights.begin(), pointLights.end(), [&pointLight](PointLight* light) { 
        return light->index == pointLight->index; 
    });
    
    if (it != pointLights.end()) {
        int removedIndex = it - pointLights.begin();
        pointLights.erase(it);

        // Update the indices of the remaining point lights
        for (PointLight* light : pointLights) {
            if (light->index > removedIndex) {
                light->index--;
            }
        }

        // Update shaders
        for (Shader* shader : shaders) {
            shader->setInt("activePointLights", pointLights.size());
            for (PointLight* light : pointLights) {
                updateShaderPoint(shader, light);
            }
        }
    }
}

// void Lights::removeSpotLight(SpotLight spotLight){
//     freeSpotIndexes.push_back(spotLight.index);

//     for (auto it = spotLights.begin(); it != spotLights.end(); ++it) {
//         if (it->index == spotLight.index) {
//             spotLights.erase(it);
//             break; 
//         }
//     }
// }

void LightManager::updateShaderDirectional(Shader* shader){
    shader->setVec3("directionalLight.direction", directionalLight.direction);
    shader->setVec3("directionalLight.phong.ambient", directionalLight.phong.ambient);
    shader->setVec3("directionalLight.phong.diffuse", directionalLight.phong.diffuse);
    shader->setVec3("directionalLight.phong.specular", directionalLight.phong.specular);
}

// void LightManager::updateShaderSpots(Shader* shader){
//     for (SpotLight light : spotLights){
//         updateShaderSpot(shader, light);
//     }
// }

void LightManager::updateShaderPoint(Shader* shader, PointLight* light){
    shader->setVec3(("pointLights[" + std::to_string(light->index) + "].position").c_str(), light->position);
    shader->setVec3(("pointLights[" + std::to_string(light->index) + "].color").c_str(), light->color);
    shader->setVec3(("pointLights[" + std::to_string(light->index) + "].phong.ambient").c_str(), light->phong.ambient);
    shader->setVec3(("pointLights[" + std::to_string(light->index) + "].phong.diffuse").c_str(), light->phong.diffuse);
    shader->setVec3(("pointLights[" + std::to_string(light->index) + "].phong.specular").c_str(), light->phong.specular);
    shader->setFloat(("pointLights[" + std::to_string(light->index) + "].attenuation.constant").c_str(), light->attenuation.constant);
    shader->setFloat(("pointLights[" + std::to_string(light->index) + "].attenuation.linear").c_str(), light->attenuation.linear);
    shader->setFloat(("pointLights[" + std::to_string(light->index) + "].attenuation.quadratic").c_str(), light->attenuation.quadratic);
}

// void Lights::updateShaderSpot(Shader* shader, SpotLight light){
//     shader->setVec3(("spotLights[" + std::to_string(light.index) + "].position").c_str(), light.position);
//     shader->setVec3(("spotLights[" + std::to_string(light.index) + "].direction").c_str(), light.direction);
//     shader->setFloat(("spotLights[" + std::to_string(light.index) + "].cutOff").c_str(), light.cutOff);
//     shader->setFloat(("spotLights[" + std::to_string(light.index) + "].outerCutOff").c_str(), light.outerCutOff);
//     shader->setVec3(("spotLights[" + std::to_string(light.index) + "].phong.ambientStrenght").c_str(), light.phong.ambient);
//     shader->setVec3(("spotLights[" + std::to_string(light.index) + "].phong.diffuseStrenght").c_str(), light.phong.diffuse);
//     shader->setVec3(("spotLights[" + std::to_string(light.index) + "].phong.specularStrenght").c_str(), light.phong.specular);
//     shader->setFloat(("spotLights[" + std::to_string(light.index) + "].constant").c_str(), light.constant);
//     shader->setFloat(("spotLights[" + std::to_string(light.index) + "].linear").c_str(), light.linear);
//     shader->setFloat(("spotLights[" + std::to_string(light.index) + "].quadratic").c_str(), light.quadratic);
// }