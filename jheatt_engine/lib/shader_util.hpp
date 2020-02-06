#ifndef __SHADER_UTIL_INCLUDED__
#define __SHADER_UTIL_INCLUDED__

#include "window_manager.hpp"
#include "file_utils.hpp"
#include "SOIL/SOIL.h"

class ShaderUtil {
public:
    static const char* DEFAULT_SHADER_PATH;
    static const char* VERTEX_SHADER_EXTENSION;
    static const char* FRAGMENT_SHADER_EXTENSION;

    static GLuint LoadShader(int shader_type, const char* vertex_shader_name);
    static std::string GetShaderPath(const char* shader_name, int shader_type);
    static bool TryCompileShader(GLuint shader, bool printErrors = true);

    static GLuint CreateAndBindVertexArray(int slot);
    static GLuint CreateAndBindVertexBufferObject(int slot, float* vertices, int size);
    static GLuint CreateAndBindElementBufferObject(int slot, GLuint* indexes, int size);
    static GLuint CreateAndBindTexture(int slot, GLenum type = GL_TEXTURE_2D);
    static bool LoadRGBTexture(const char* file_path, GLenum type = GL_TEXTURE_2D);
};

#endif 