#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(Shader& shader, const int usage, const float vertexData[], const int vertexDataSize, const int attributeAmount, const int attributeLenghts[], const unsigned int indices[], const int indicesAmount) : shader(shader), indicesAmount(indicesAmount){

    /* Offsets and Stride */
    int attributeOffsets[attributeAmount];
    int stride = 0;

    attributeOffsets[0] = 0;
    stride += sizeof(float) * attributeLenghts[0];
    if (attributeAmount > 1){
        for (int i = 1; i < attributeAmount; i++){
            int attributeSize = sizeof(float) * attributeLenghts[i];
            attributeOffsets[i] = attributeSize + attributeOffsets[i - 1];
            stride += attributeSize;
        }
    }

    /* Generate buffers */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* VAO */
    glBindVertexArray(VAO);

    /* VBO */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize , vertexData, usage);

    /* EBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesAmount, indices, usage);

    /* Vertex Attributes */
    for (int i = 0; i < attributeAmount; i++){
        glVertexAttribPointer(i, attributeLenghts[i], GL_FLOAT, GL_FALSE, stride, (void*)(uintptr_t)attributeOffsets[i]);
        glEnableVertexAttribArray(i);
    }

    /* Cleanup */
    /* note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind */
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Clears the VBO

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); // Clears the VAO

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Clears the EBO
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::draw() const{
    bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, indicesAmount, GL_UNSIGNED_INT, 0);
}

// private
void Mesh::bind() const{
    glBindVertexArray(VAO);
}