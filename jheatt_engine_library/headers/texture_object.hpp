#ifndef __TEXTURE_OBJECT_INCLUDED__
#define __TEXTURE_OBJECT_INCLUDED__

#include "engine.hpp"
#ifdef JHEATT_ENGINE_EXPORTS  
    #include "SOIL/SOIL.h"
#endif

class Shader;

class TextureObject {
private:
    GLenum _format = GL_RGB;
    GLenum _type = GL_TEXTURE_2D;

public:
    unsigned int unitSlot;
    TextureUsage Usage;
    const char* FilePath;

    GLenum textureType = GL_TEXTURE_2D;
    GLuint handle = 0;
    int Width = 0, Height = 0;
    
    JHEATT_ENGINE_API TextureObject(const char * textureFilePath, int slot = 0, TextureUsage usage = TextureUsage::DIFFUSE, GLenum format = GL_RGB, GLenum type = GL_TEXTURE_2D);
    void UseTexture(Shader* shader);

    JHEATT_ENGINE_API ~TextureObject();
};

#endif 