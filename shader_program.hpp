#ifndef __SHADER_PROGRAM_INCLUDED__
#define __SHADER_PROGRAM_INCLUDED__
#include "shader_util.hpp"

class ShaderProgram {
  public:
    GLuint ShaderProgram;
    GLuint VertexShader;
    GLuint FragmentShader;

    GLint PositionAttribute;    
    GLint ColorAttribute;
    GLint TextureAttribute;

    bool ConfigureDefaultShaderProgram(); 
    void ConfigureDefaultShaderAttributes();

    ~ShaderProgram(); 
};

#endif 