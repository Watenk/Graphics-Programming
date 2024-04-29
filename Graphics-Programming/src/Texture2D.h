#pragma once

#include <string>

class Texture2D{
public:
    /**
     * @param texturePath the path with fileExtention where the texture resides
     * @param wrappingMode the way OpenGL wraps the texture (GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE or GL_CLAMP_TO_BORDER)
     * @param minimizeFilterMode how OpenGL renders a object if its smaler than the original with the mipmap filter included (GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR or GL_LINEAR_MIPMAP_LINEAR)
     * @param magnifyFilterMode how OpenGL renders a object if its bigger than the original (GL_NEAREST or GL_LINEAR)
    */
    Texture2D(const std::string& texturePath, const int wrappingMode, const int minimizeFilterMode, const int magnifyFilterMode);

    void bind() const;

private:
    unsigned int texture;
};