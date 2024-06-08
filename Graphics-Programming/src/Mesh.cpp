#include "Mesh.h"

#include <glad/glad.h>
#include <iostream>

Mesh::Mesh(const int usage, const std::vector<float> vertices, const std::vector<unsigned int> indices, const std::vector<int> attributes) 
          : vertices(vertices), indices(indices){

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
}

void Mesh::draw(Transform transform, Shader* shader, Material* material, Camera* cam) const{
    bind();
    shader->bind();

    /* MVP Uniforms */
    shader->setMatrix4("model", transform.getModelMatrix());
    shader->setMatrix4("view", cam->getViewMatrix());
    shader->setMatrix4("projection", cam->getProjectionMatrix());

    /* Material Uniforms */
    /* Diffuse */
    int diffuseIndex = 0;
    glActiveTexture(GL_TEXTURE0 + diffuseIndex);
    shader->setInt("material.diffuse", diffuseIndex);
    if (material->diffuseTexture != nullptr) material->diffuseTexture->bind();
    else glBindTexture(GL_TEXTURE_2D, 0);
    
    /* Specular */
    int specularIndex = 1;
    glActiveTexture(GL_TEXTURE0 + specularIndex);
    shader->setInt("material.specular", specularIndex);
    if (material->specularTexture != nullptr) material->specularTexture->bind();
    else glBindTexture(GL_TEXTURE_2D, 0);
    
    /* Normal */
    int normalIndex = 2;
    glActiveTexture(GL_TEXTURE0 + normalIndex);
    shader->setInt("material.normal", normalIndex);
    if (material->normalTexture != nullptr) material->normalTexture->bind();
    else glBindTexture(GL_TEXTURE_2D, 0);

    /* Extra Textures */
    if (material->extraTextures.size() > 0){
        int extraIndex = 3;
        int extraCount = 0;
        for (Texture2D* texture : material->extraTextures){
            glActiveTexture(GL_TEXTURE0 + extraIndex);
            shader->setInt("extraTextures.extra" + extraCount, extraIndex);
            texture->bind();
            extraCount++;
            extraIndex++;
        }
    }

    shader->setFloat("material.shininess", 64.0f);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::bind() const{
    glBindVertexArray(VAO);
}