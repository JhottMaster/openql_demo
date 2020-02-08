#ifndef __SHADER_UTIL_INCLUDED__
#define __SHADER_UTIL_INCLUDED__

#include "window_manager.hpp"
#include "file_utils.hpp"
#include "SOIL/SOIL.h"

class ShaderUtil {
public:
    static GLuint CreateAndBindVertexArray(int slot);
    static GLuint CreateAndBindVertexBufferObject(int slot, float* vertices, int size);
    static GLuint CreateAndBindElementBufferObject(int slot, GLuint* indexes, int size);
    static GLuint CreateAndBindTexture(int slot, GLenum type = GL_TEXTURE_2D);
    static bool LoadRGBTexture(const char* file_path, GLenum type = GL_TEXTURE_2D);
};

#endif 