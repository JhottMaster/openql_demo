#include "shader_util.hpp"


// Should this go into some sort of global manager?
GLuint ShaderUtil::CreateAndBindVertexArray(int slot) {
    GLuint vertexArrayObjectHandle;
    glGenVertexArrays(slot, &vertexArrayObjectHandle);
    glBindVertexArray(vertexArrayObjectHandle);
    return vertexArrayObjectHandle;
}

// Should this go into some sorpt of global manager?
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
bool ShaderUtil::LoadRGBTexture(const char* file_path, GLenum type) {
    int width, height;
    unsigned char* image = SOIL_load_image(file_path, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    if (image == nullptr) {
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