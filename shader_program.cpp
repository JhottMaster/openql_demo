#include "shader_program.hpp"

// This should probably go into its own class for shader programs:
bool ShaderProgram::ConfigureDefaultShaderProgram() {
  VertexShader = ShaderUtil::LoadShader(GL_VERTEX_SHADER, "2d_triangle");
  if (!ShaderUtil::TryCompileShader(VertexShader)) return false;
  
  FragmentShader = ShaderUtil::LoadShader(GL_FRAGMENT_SHADER, "2d_triangle");
  if (!ShaderUtil::TryCompileShader(FragmentShader)) return false;

	// Now we'll need a complete program "pipeline"
  ShaderProgram = glCreateProgram();
  glAttachShader(ShaderProgram, VertexShader);
  glAttachShader(ShaderProgram, FragmentShader);
  // Fragment shader is allowed to write to multiple buffers, so explicitly specify
  // which output is written to which buffer (0) before linking the program:
  glBindFragDataLocation(ShaderProgram, 0, "outColor");
  glLinkProgram(ShaderProgram); // Link it
  glUseProgram(ShaderProgram); // Use it

  // We were successful
  return true;
}

// This should probably go into its own class for shader programs:
void ShaderProgram::ConfigureDefaultShaderAttributes() {
	// Get the position of the "postition" argument in vertex shader:
  PositionAttribute = glGetAttribLocation(ShaderProgram, "position");
  // Describe the input type for PositionAttribute (vertices array)
  glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(PositionAttribute);

	// Get the position of the "color" argument in vertex shader:
  ColorAttribute = glGetAttribLocation(ShaderProgram, "color");
  // Describe the input type for ColorAttribute (color position in vertices array)
  glVertexAttribPointer(ColorAttribute, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
  glEnableVertexAttribArray(ColorAttribute);

	// Get the position of the "texcoord" argument in vertex shader:
	TextureAttribute = glGetAttribLocation(ShaderProgram, "texcoord");
	glVertexAttribPointer(TextureAttribute, 2, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(5*sizeof(GLfloat)));
	glEnableVertexAttribArray(TextureAttribute);
}

// Destructor cleans up objects
ShaderProgram::~ShaderProgram(void) {
  glDeleteProgram(ShaderProgram);
  glDeleteShader(FragmentShader);
  glDeleteShader(VertexShader);
}
