#ifndef __SHADER_PROGRAM_INCLUDED__
#define __SHADER_PROGRAM_INCLUDED__
#include "shader_util.hpp"

class ShaderProgram {
public:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

    GLint positionAttribute;
    GLint colorAttribute;
    GLint textureAttribute;

    bool ConfigureDefaultShaderProgram();
    void ConfigureDefaultShaderAttributes();

    ~ShaderProgram();
};

#endif 