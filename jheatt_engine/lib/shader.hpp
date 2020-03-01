#ifndef __SHADER_INCLUDED__
#define __SHADER_INCLUDED__

#include "engine.hpp"
#include "file_utils.hpp"

class Shader {
private:
    GLuint LoadShader(int shader_type, const char* vertex_shader_name);
    std::string GetShaderPath(const char* shader_name, int shader_type);
    bool TryCompileShader(GLuint shader, bool printErrors = true);


public:
    GLuint shaderProgram;
    bool compilationFailed;
    char lastErrorCallStack[512];

    static const char* DEFAULT_SHADER_PATH;
    static const char* VERTEX_SHADER_EXTENSION;
    static const char* FRAGMENT_SHADER_EXTENSION;

    Shader(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);

    void UseShader();

    void SetBoolVariable(const std::string &name, bool value) const;
    void SetIntVariable(const std::string &name, int value) const;
    void SetFloatVariable(const std::string &name, float value) const;
    void SetVec2Variable(const std::string &name, glm::vec2 &value) const;
    void SetVec3Variable(const std::string &name, glm::vec3 &value) const;
    void SetFloatMatrixVariable(const std::string &name, glm::mat4 value) const;

    ~Shader();
};

#endif 