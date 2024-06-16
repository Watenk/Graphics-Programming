#include "Firefly.h"

#include "util/PrimitiveUtil.h"

Firefly::Firefly(glm::vec3 centerPoint, glm::vec3 color, Shader* colorShader, Camera* cam) : centerPoint(centerPoint){
    gameObject = new GameObject(PrimitiveUtil::getCube(), colorShader, new Material(), cam);
    light = new PointLight();
    light->color = color;
    light->phong.ambient = glm::vec3(0.005f);
    light->phong.diffuse = glm::vec3(0.1f);
}

void Firefly::update(float deltaTime){
    // Movement
    glm::vec3 randomDirection = glm::sphericalRand(1.0f);
    glm::vec3 movement = randomDirection * glm::linearRand(0.0f, radius);
    gameObject->transform.move(glm::normalize(movement) * movementSpeed * deltaTime);

    // boundary checking
    glm::vec3 directionToCenter = centerPoint - gameObject->transform.getPosition();
    float distanceToCenter = glm::length(directionToCenter);
    if (distanceToCenter > radius) {
       gameObject->transform.move(glm::normalize(directionToCenter) * (distanceToCenter - radius));
    }

   light->position = gameObject->transform.getPosition();
}