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

// Should this go into some sort of global manager?
GLuint ShaderUtil::CreateAndBindVertexArray(int slot) {
	GLuint vertexArrayObjectHandle;
  glGenVertexArrays(slot, &vertexArrayObjectHandle);
  glBindVertexArray(vertexArrayObjectHandle);  
	return vertexArrayObjectHandle;
}

// Should this go into some sort of global manager?
GLuint ShaderUtil::CreateAndBindVertexBufferObject(int slot, float* vertices, int size) {
  // Create device object to store vertex data in graphics card memory:
  GLuint vertexBufferObjectHandle;
  glGenBuffers(slot, &vertexBufferObjectHandle); // Create device and assign to handle
  // Let's make it the active object so we can do stuff with it:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);  
	return vertexBufferObjectHandle;
}

// Should this go into some sort of global manager?
GLuint ShaderUtil::CreateAndBindElementBufferObject(int slot, GLuint* indexes, int size) {
	// Create an element array
  GLuint elementBufferObjectHanle;
  glGenBuffers(slot, &elementBufferObjectHanle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectHanle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexes, GL_STATIC_DRAW);
	return elementBufferObjectHanle;
}

// Should this go into some sort of texture manager?
GLuint ShaderUtil::CreateAndBindTexture(int slot, GLenum type) {
	// Create device object able to store texture in graphics card memory:
  GLuint textureObjectHandle;
  glGenTextures(slot, &textureObjectHandle);
  glBindTexture(type, textureObjectHandle); // Bind so we can apply operations to it
	return textureObjectHandle;
}

// Should this go into some sort of texture manager?
bool ShaderUtil::LoadRGBTexture(const char * file_path, GLenum type) {
	int width, height;
  unsigned char* image = SOIL_load_image(file_path, &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  if(image == nullptr) {
    printf("SOIL Texture Error; Could not load '%s':\n'%s'\n\n", file_path, SOIL_last_result());
    return false;
  }
  SOIL_free_image_data(image);

  glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}