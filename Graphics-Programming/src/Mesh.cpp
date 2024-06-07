#include "Mesh.h"

#include <glad/glad.h>
#include <iostream>

Mesh::Mesh(const int usage, const std::vector<float> vertices, const std::vector<unsigned int> indices, const Camera* cam, const std::vector<Texture2D*> textures, const std::vector<int> attributes) 
          : vertices(vertices), indices(indices), cam(cam), textures(textures){

    /* Generate Buffers */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* VAO */
    glBindVertexArray(VAO);

    /* VBO */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), usage);

    /* EBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), usage);

    /* Vertex Attributes */
    /* Calc vertex attributes stride and offsets */
    int attributeSizes[attributes.size()];
    int attributeOffsets[attributes.size()];
    int stride = 0;

    attributeSizes[0] = sizeof(float) * attributes[0];
    stride += attributeSizes[0];
    attributeOffsets[0] = 0;
    if (attributes.size() > 1){
        for (int i = 1; i < attributes.size(); i++){
            attributeSizes[i] = sizeof(float) * attributes[i];
            stride += attributeSizes[i];
            attributeOffsets[i] = attributeSizes[i - 1] + attributeOffsets[i - 1];
        }
    }

    /* Set Vertex Attributes */
    for (int i = 0; i < attributes.size(); i++){
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, stride, (void*)(uintptr_t)attributeOffsets[i]);
        glEnableVertexAttribArray(i);
    }
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    for (Texture2D* texture : textures){
        delete texture;
    }
}

void Mesh::draw(Shader* shader) const{
    bind();
    updateShaderUniforms(shader);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::updateShaderUniforms(Shader* shader) const{

    /* Shader MVP Uniforms */
    shader->setMatrix4("model", transform.getModelMatrix());
    shader->setMatrix4("view", cam->getViewMatrix());
    shader->setMatrix4("projection", cam->getProjectionMatrix());

    /* Shader Material Uniforms */
    int diffuseIndex = 0;
    int specularIndex = 0;
    for (Texture2D* texture : textures){
        texture->bind();
        if (texture->type == TextureType::diffuse){
            std::string textureName = "material.diffuse" + std::to_string(diffuseIndex);
            shader->setInt(textureName.c_str(), diffuseIndex + specularIndex);
            diffuseIndex++;
        }
        else if (texture->type == TextureType::specular){
            std::string textureName = "material.specular" + std::to_string(specularIndex);
            shader->setInt(textureName.c_str(), diffuseIndex + specularIndex);
            specularIndex++;
        }
    }
    shader->setFloat("material.shininess", 64.0f);
}

void Mesh::bind() const{
    glBindVertexArray(VAO);

    /* Textures */
    for (int i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->bind();
    }
}

// void Mesh::unBind() const{
//     /* note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind */
//     glBindBuffer(GL_ARRAY_BUFFER, 0); // Clears the VBO

//     // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//     // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//     glBindVertexArray(0); // Clears the VAO

//     // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Clears the EBO
// }