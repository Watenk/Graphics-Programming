#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Shader* shader, Material* material, Camera* cam) : mesh(mesh), shader(shader), material(material), cam(cam) {}

void GameObject::draw() const{
    mesh->draw(transform, shader, material, cam);
}