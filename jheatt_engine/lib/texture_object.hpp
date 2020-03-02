#ifndef __TEXTURE_OBJECT_INCLUDED__
#define __TEXTURE_OBJECT_INCLUDED__

#include "engine.hpp"
#include "SOIL/SOIL.h"

class Shader;

class TextureObject {
private:
    GLenum _format = GL_RGB;
    GLenum _type = GL_TEXTURE_2D;

public:
    unsigned int unitSlot;
    TextureUsage Usage;
    const char* FilePath;

    GLenum textureType;
    GLuint handle;
    int Width, Height;
    
    TextureObject(const char * textureFilePath, int slot = 0, TextureUsage usage = DIFFUSE, GLenum format = GL_RGB, GLenum type = GL_TEXTURE_2D);
    void UseTexture(Shader* shader);

    ~TextureObject();
};

#endif 