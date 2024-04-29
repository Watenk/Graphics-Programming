#include "Texture2D.h"

#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture2D::Texture2D(const std::string& texturePath, const int sourceFormat, const int wrappingMode, const int minimizeFilterMode, const int magnifyFilterMode){

    stbi_set_flip_vertically_on_load(true);  

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 

    /* Texture Wrapping */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingMode);

    /* Texture Filtering */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minimizeFilterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifyFilterMode);

    /* Load Texture */
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load Texture2D" << std::endl;
    }

    /* Cleanup */
    stbi_image_free(data);
}

Texture2D::~Texture2D(){
    glDeleteTextures(1, &texture);
}

void Texture2D::bind() const{
    glBindTexture(GL_TEXTURE_2D, texture);
}