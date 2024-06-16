#include "Firefly.h"

#include "util/PrimitiveUtil.h"

Firefly::Firefly(Camera* cam){
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    gameObject = new GameObject(PrimitiveUtil::getCube(), new Shader("color"), new Material(), cam);
}

void Firefly::update(float deltaTime){
    glm::vec3 randomDirection = glm::sphericalRand(1.0f);
    glm::vec3 movement = randomDirection * glm::linearRand(0.0f, radius);
    gameObject->transform.move(glm::normalize(movement) * movementSpeed * deltaTime);

    // boundary checking
    glm::vec3 directionToCenter = centerPoint - gameObject->transform.getPosition();
    float distanceToCenter = glm::length(directionToCenter);
    if (distanceToCenter > radius) {
       gameObject->transform.move(glm::normalize(directionToCenter) * (distanceToCenter - radius));
    }

}

float Firefly::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(max-min));
}