#include "window_manager.hpp"
#include "file_utils.hpp"
#include "shader_util.hpp"
#include "SOIL.h"

using namespace glm;

// Declarations
bool windowShouldStayOpen();

WindowManager window;


int main() {

  
  window.initialize("Open GL Demo", 1000, 768);

  float vertices[] = {
  // Position         Color                 Texcoords
    -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f, // Top-left
     0.5f,  0.5f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f, // Top-right
     0.5f, -0.5f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f  // Bottom-left
  };

  // Create device object to store vertex data in graphics card memory:
  GLuint vertexBufferObjectHandle;
  glGenBuffers(1, &vertexBufferObjectHandle); // Create device and assign to handle

  // Let's make it the active object so we can do stuff with it:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create an element array
  GLuint elementBufferObjectHandle;
  glGenBuffers(1, &elementBufferObjectHandle);

  GLuint elementIndexTriangles[] = {
      0, 1, 2,
      2, 3, 0
  };

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectHandle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementIndexTriangles), elementIndexTriangles, GL_STATIC_DRAW);

  // Build, compile, and link our vertex and fragment shares into a program:
  GLuint defaultShaderProgram = ShaderUtil::BuildDefaultShaderProgram();
  glUseProgram(defaultShaderProgram); // Use shader program
  
  ShaderUtil::ConfigureDefaultShaderAttributes(defaultShaderProgram);
  
  GLuint vertexArrayObjectHandle;
  glGenVertexArrays(1, &vertexArrayObjectHandle);
  glBindVertexArray(vertexArrayObjectHandle);  

  // Create device object able to store texture in graphics card memory:
  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex); // Bind so we can apply operations to it
 
  // Load Texture: 
  // Black/white checkerboard
  int width, height;
  unsigned char* image = SOIL_load_image("resources/images/dark_wooden_create.jpg", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image); // Free SOIL's handle to the image/memory since it's in GPU now

  // Configure texture parameters:
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat texture X
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat texture Y
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glGenerateMipmap(GL_TEXTURE_2D);

  while(windowShouldStayOpen()) // Check if the ESC key was pressed or the window was closed
  {  
    window.clearCurrentBuffer();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window.swapBuffersAndCheckForEvents();
  } 

  // Free up all the memoriez:
  glDeleteTextures(1, &tex);

  glDeleteProgram(defaultShaderProgram);
  // glDeleteShader(fragmentShader);
  // glDeleteShader(vertexShader);
  glDeleteBuffers(1, &elementBufferObjectHandle);
  glDeleteBuffers(1, &vertexBufferObjectHandle);
  glDeleteVertexArrays(1, &vertexArrayObjectHandle);

  return 0;
}

bool windowShouldStayOpen() {
  if (window.windowEspaceKeyHit()) return false;
  if (window.windowShouldClose()) return false;
  return true;
}


