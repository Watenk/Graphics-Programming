#include "GameObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

GameObject::GameObject(Mesh* mesh, Shader* shader, std::vector<Texture2D*> textures, Camera* cam) : mesh(mesh), shader(shader), textures(textures), cam(cam) {

    mesh->bind();
    shader->bind();

    /* Shader Texture Uniforms */
    int index = 0;
    for (Texture2D* texture : textures){
        texture->bind();
        std::string textureName = "texture" + std::to_string(index);
        glUniform1i(glGetUniformLocation(shader->getID(), textureName.c_str()), index);
        index++;
    }
}

GameObject::~GameObject(){
    delete(mesh);
    delete(shader);
    for (Texture2D* texture : textures){
        delete(texture);
    }
}

void GameObject::draw() const{
    bind();
    glDrawElements(GL_TRIANGLES, mesh->getIndicesAmount(), GL_UNSIGNED_INT, 0);
}

void GameObject::bind() const{
    mesh->bind();
    shader->bind();
    bindTextures();

    /* Shader MVP Uniforms */
    glm::mat4 model = transform.getModelMatrix();
    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 projection = cam->getProjectionMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void GameObject::bindTextures() const{
    for (int i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->bind();
    }
}