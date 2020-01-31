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