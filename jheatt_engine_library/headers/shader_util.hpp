#ifndef __SHADER_UTIL_INCLUDED__
#define __SHADER_UTIL_INCLUDED__

#include "engine.hpp"

class ShaderUtil {
public:
    static GLuint CreateAndBindVertexArray(int slot);
    static GLuint CreateAndBindVertexBufferObject(int slot, float* vertices, int size);
    static GLuint CreateAndBindElementBufferObject(int slot, GLuint* indexes, int size);
};

#endif 