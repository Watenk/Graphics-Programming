#include "Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

Model::Model(Mesh* mesh, Shader* shader, Camera* cam) : mesh(mesh), shader(shader), cam(cam) {
    mesh->changeShader(shader);
}

Model::~Model(){
    delete mesh;
    delete shader;
}

void Model::draw() const{

    // /* Update Shader MVP Uniforms */
    shader->setMatrix4("model", transform.getModelMatrix());
    shader->setMatrix4("view", cam->getViewMatrix());
    shader->setMatrix4("projection", cam->getProjectionMatrix());

    mesh->draw();
}
