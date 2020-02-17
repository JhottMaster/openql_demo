#include "shader_util.hpp"

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