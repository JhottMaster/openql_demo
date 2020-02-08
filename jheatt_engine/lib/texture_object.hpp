#ifndef __TEXTURE_OBJECT_INCLUDED__
#define __TEXTURE_OBJECT_INCLUDED__

#include "window_manager.hpp"
#include "file_utils.hpp"
#include "SOIL/SOIL.h"

class TextureObject {
private:
    int unitSlot;

public:
    GLenum textureType;
    GLuint handle;
    int Width, Height;
    
    TextureObject(const char * textureFilePath, int slot = 0, GLenum format = GL_RGB, GLenum type = GL_TEXTURE_2D);
    void Bind();

    ~TextureObject();
};

#endif 