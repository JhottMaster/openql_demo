#include "shader_util.hpp"

const char * ShaderUtil::DEFAULT_SHADER_PATH = "shaders/";
const char * ShaderUtil::VERTEX_SHADER_EXTENSION = ".vert";
const char * ShaderUtil::FRAGMENT_SHADER_EXTENSION = ".frag";

GLuint ShaderUtil::LoadShader(int shader_type, const char * shader_name) {
	// Create a vertex shader object on the device to store shader program:
  GLuint shader = glCreateShader(shader_type);

	// Load shader program from file:
	std::string path = GetShaderPath(shader_name, shader_type);
  std::string contents = FileUtils::ReadString(path.c_str());

	// Define shader:
  const char * pointer = contents.c_str();
  glShaderSource(shader, 1, &pointer, NULL);

	return shader;
}

bool ShaderUtil::TryCompileShader(GLuint shader, bool printErrors) {
  glCompileShader(shader);

  GLint status; // This will store compilation output result
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status); // Check result

	// Output "call stack" if we can get it:
  if (status != GL_TRUE && printErrors) { 
    printf("Could not compile vertex shader! Callstack: \n"); 
    char buffer[512];
    glGetShaderInfoLog(shader, 512, NULL, buffer);
  }
	return (status == GL_TRUE);
}

// This should probably go into its own class for shader programs:
GLuint ShaderUtil::BuildDefaultShaderProgram() {
  GLuint vertexShader = ShaderUtil::LoadShader(GL_VERTEX_SHADER, "2d_triangle");
  if (!ShaderUtil::TryCompileShader(vertexShader)) return 0;
  
  GLuint fragmentShader = ShaderUtil::LoadShader(GL_FRAGMENT_SHADER, "2d_triangle");
  if (!ShaderUtil::TryCompileShader(fragmentShader)) return 0;

	// Now we'll need a complete program "pipeline"
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  // Fragment shader is allowed to write to multiple buffers, so explicitly specify
  // which output is written to which buffer (0) before linking the program:
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram); // Link it
  
	return shaderProgram;
}

// This should probably go into its own class for shader programs:
void ShaderUtil::ConfigureDefaultShaderAttributes(GLuint defaultShaderProgram) {
	// Get the position of the "postition" argument in vertex shader:
  GLint posAttrib = glGetAttribLocation(defaultShaderProgram, "position");
  // Describe the input type for posAttrib (vertices array)
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(posAttrib);

	// Get the position of the "color" argument in vertex shader:
  GLint colorAttrib = glGetAttribLocation(defaultShaderProgram, "color");
  // Describe the input type for colorAttrib (color position in vertices array)
  glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));
  glEnableVertexAttribArray(colorAttrib);

	// Get the position of the "texcoord" argument in vertex shader:
	GLint texAttrib = glGetAttribLocation(defaultShaderProgram, "texcoord");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)(5*sizeof(GLfloat)));
	glEnableVertexAttribArray(texAttrib);
}

std::string ShaderUtil::GetShaderPath(const char * shader_name, int shader_type) {
	std::string fullPath = "";

	fullPath.append(DEFAULT_SHADER_PATH);
	fullPath.append(shader_name);

	// Figure out the right extension for the type of shader:
	switch (shader_type)
	{
		case GL_VERTEX_SHADER:
			fullPath.append( ShaderUtil::VERTEX_SHADER_EXTENSION);
			break;
		case GL_FRAGMENT_SHADER:
			fullPath.append( ShaderUtil::FRAGMENT_SHADER_EXTENSION);
			break;
		default:
			printf("ERROR: Unknown shader type code %d!", shader_type); 
	}
	return fullPath;
}