#include "GameObject.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

GameObject::GameObject(Mesh mesh, Shader shader, std::vector<Texture2D> textures) : mesh(mesh), shader(shader), textures(textures) {
    
    /* Set Texture Uniforms */
    int index = 0;
    for (Texture2D texture : textures){
        glUniform1i(glGetUniformLocation(shader.getID(), "texture" + index), index);
        index++;
    }
}

GameObject::~GameObject(){

}

void GameObject::bind(glm::mat4 model, glm::mat4 view, glm::mat4 projection){
    mesh.bind();
    shader.bind();
}