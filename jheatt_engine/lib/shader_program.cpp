#include "shader_program.hpp"

// This should probably go into its own class for shader programs:
bool ShaderProgram::ConfigureDefaultShaderProgram() {
    vertexShader = ShaderUtil::LoadShader(GL_VERTEX_SHADER, "2d_triangle");
    if (!ShaderUtil::TryCompileShader(vertexShader)) return false;

    fragmentShader = ShaderUtil::LoadShader(GL_FRAGMENT_SHADER, "2d_triangle");
    if (!ShaderUtil::TryCompileShader(fragmentShader)) return false;

    // Now we'll need a complete program "pipeline"
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Fragment shader is allowed to write to multiple buffers, so explicitly specify
    // which output is written to which buffer (0) before linking the program:
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram); // Link it

    GLint status; // This will store compilation output result
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status) {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, buffer);
        printf("Could not compile shader program! Callstack:\n%s", buffer);
        return false;
    }

    glUseProgram(shaderProgram); // Use it
    
    // We were successful
    return true;
}

// This should probably go into its own class for shader programs:
void ShaderProgram::ConfigureDefaultShaderAttributes() {
    // Get the position of the "postition" argument in vertex shader:
    positionAttribute = glGetAttribLocation(shaderProgram, "position");
    // Describe the input type for positionAttribute (vertices array)
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(positionAttribute);

    // Get the position of the "color" argument in vertex shader:
    colorAttribute = glGetAttribLocation(shaderProgram, "color");
    // Describe the input type for colorAttribute (color position in vertices array)
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttribute);

    // Get the position of the "texcoord" argument in vertex shader:
    textureAttribute = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureAttribute);
}

// Destructor cleans up objects
ShaderProgram::~ShaderProgram(void) {
    glDeleteProgram(shaderProgram);

    // Delete shaders- technically we could actually delete them right 
    // after linking the shader program, but we do it here:
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}
