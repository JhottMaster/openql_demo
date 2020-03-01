#include "shader.hpp"

const char* Shader::DEFAULT_SHADER_PATH = "shaders/";
const char* Shader::VERTEX_SHADER_EXTENSION = ".vert";
const char* Shader::FRAGMENT_SHADER_EXTENSION = ".frag";

Shader::Shader(const char * vertexShaderFileName, const char * fragmentShaderFileName) {
	compilationFailed = false;

	GLuint vertexShader = Shader::LoadShader(GL_VERTEX_SHADER, vertexShaderFileName);
	if (!Shader::TryCompileShader(vertexShader)) return;

	GLuint fragmentShader = Shader::LoadShader(GL_FRAGMENT_SHADER, fragmentShaderFileName);
	if (!Shader::TryCompileShader(fragmentShader)) return;

	// Now we'll need a complete program "pipeline"
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Fragment shader is allowed to write to multiple buffers, so explicitly specify
	// which output is written to which buffer (0) before linking the program:
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram); // Link it

	GLint status; 
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	// Output "call stack" if we can get it:
	if (status != GL_TRUE) {
			compilationFailed = true;
			printf("Could not compile shader program!");
			glGetProgramInfoLog(shaderProgram, 512, NULL, lastErrorCallStack);
			return;
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::UseShader() {
	if (compilationFailed) {
		printf("WARNING: Attempting to configure attributes after failed shader compilation");
	}
	glUseProgram(shaderProgram);
}

void Shader::SetBoolVariable(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}

void Shader::SetIntVariable(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void Shader::SetFloatVariable(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
} 

void Shader::SetVec2Variable(const std::string &name, glm::vec2 &value) const
{ 
		glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
} 

void Shader::SetVec3Variable(const std::string &name, glm::vec3 &value) const
{ 
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]); 
} 

void Shader::SetFloatMatrixVariable(const std::string &name, glm::mat4 value) const
{ 
		int variableLocation = glGetUniformLocation(shaderProgram, name.c_str());
  	glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(value));
} 

GLuint Shader::LoadShader(int shader_type, const char* shader_name) {
    // Create a vertex shader object on the device to store shader program:
    GLuint shader = glCreateShader(shader_type);

    // Load shader program from file:
    std::string path = GetShaderPath(shader_name, shader_type);
    std::string contents = FileUtils::ReadString(path.c_str());

    // Define shader:
    const char* pointer = contents.c_str();
    glShaderSource(shader, 1, &pointer, NULL);

    return shader;
}

bool Shader::TryCompileShader(GLuint shader, bool printErrors) {
    glCompileShader(shader);

    GLint status; // This will store compilation output result
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status); // Check result

    // Output "call stack" if we can get it:
    if (status != GL_TRUE && printErrors) {
				compilationFailed = true;
        printf("Could not compile shader!");
        glGetShaderInfoLog(shader, 512, NULL, lastErrorCallStack);
    }
    return (status == GL_TRUE);
}

std::string Shader::GetShaderPath(const char* shader_name, int shader_type) {
    std::string fullPath = "";

    fullPath.append(DEFAULT_SHADER_PATH);
    fullPath.append(shader_name);

    // Figure out the right extension for the type of shader:
    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        fullPath.append(Shader::VERTEX_SHADER_EXTENSION);
        break;
    case GL_FRAGMENT_SHADER:
        fullPath.append(Shader::FRAGMENT_SHADER_EXTENSION);
        break;
    default:
        printf("ERROR: Unknown shader type code %d!", shader_type);
    }
    return fullPath;
}

// Destructor cleans up objects
Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

