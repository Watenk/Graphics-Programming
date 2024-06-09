#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 SIZE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::quat ROTATION = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

class Transform{

public:
    /* Parent-Child */
    Transform* parent;
    std::vector<Transform*> children;

private:
    /* Transform - World Position */
    glm::vec3 position;
    glm::vec3 size;
    glm::quat rotation;

    /* LocalTransform - The position of this transform relative to its parent. */
    glm::vec3 localPosition;
    glm::vec3 localSize;
    glm::quat localRotation;

public:
    Transform(glm::vec3 position = POSITION, glm::vec3 size = SIZE, glm::quat rotation = ROTATION);
    Transform(Transform* parent, glm::vec3 position = POSITION, glm::vec3 size = SIZE, glm::quat rotation = ROTATION);

    /* Model Matrix */
    glm::mat4 getModelMatrix() const;

    /* Directions */
    glm::vec3 getFront() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    /* Transform */
    glm::vec3 getPosition() const;
    glm::vec3 getSize() const;
    glm::vec3 getEuler() const;
    glm::quat getRotation() const;
    glm::vec3 getLocalPosition() const;
    glm::vec3 getLocalSize() const;
    glm::quat getLocalRotation() const;
    void setPosition(const glm::vec3 newPosition);
    void setSize(const glm::vec3 newSize);
    void setRotation(const glm::quat newRotation);
    void setRotation(const glm::vec3& eulerDegrees);
    void setParent(Transform* parent);

    /* Transform interactions */
    void move(const glm::vec3& moveAmount);
    void scale(const glm::vec3& scaleAmount);
    void rotate(const glm::vec3& rotateAmount);
};