#pragma once

#include <string>
#include <glad/glad.h>
#include <glfw/glfw3.h>

const int WRAPPINGMODE = GL_REPEAT;
const int MINIMIZEFILTERMODE = GL_LINEAR_MIPMAP_LINEAR;
const int MAGNIFYFILTERMODE = GL_LINEAR;

enum TextureType{
    diffuse,
    specular
};

class Texture2D{
public:
    /**
     * @param texturePath the path with fileExtention where the texture resides
     * @param wrappingMode the way OpenGL wraps the texture (GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE or GL_CLAMP_TO_BORDER)
     * @param minimizeFilterMode how OpenGL renders a object if its smaler than the original with the mipmap filter included (GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR or GL_LINEAR_MIPMAP_LINEAR) 
     * @param magnifyFilterMode how OpenGL renders a object if its bigger than the original (GL_NEAREST or GL_LINEAR)
    */
    Texture2D(const std::string& texturePath, const TextureType type, const int wrappingMode = WRAPPINGMODE, const int minimizeFilterMode = MINIMIZEFILTERMODE, const int magnifyFilterMode = MAGNIFYFILTERMODE);
    ~Texture2D();

    void bind() const;

    TextureType type;
    std::string texturePath;

private:
    unsigned int texture;
};