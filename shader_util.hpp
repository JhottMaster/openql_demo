#ifndef __SHADER_UTIL_INCLUDED__
#define __SHADER_UTIL_INCLUDED__
#include "window_manager.hpp"
#include "file_utils.hpp"

class ShaderUtil {
  public:
    static const char * DEFAULT_SHADER_PATH;
    static const char * VERTEX_SHADER_EXTENSION;
    static const char * FRAGMENT_SHADER_EXTENSION;
  
    static GLuint LoadShader(int shader_type, const char * vertex_shader_name);
    static std::string GetShaderPath(const char * shader_name, int shader_type);
    static bool TryCompileShader(GLuint shader, bool printErrors = true);
    static GLuint BuildDefaultShaderProgram();
    static void ConfigureDefaultShaderAttributes(GLuint defaultShaderProgram);
};

#endif 