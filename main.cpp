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
  //  Position      Color             Texcoords
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
  };

  // Create device object to store vertex data in graphics card memory:
  GLuint vertexBufferObjectHandle;
  glGenBuffers(1, &vertexBufferObjectHandle); // Create device and assign to handle

  // Let's make it the active object so we can do stuff with it:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // // Create an element array
  // GLuint elementBufferObjectHanle;
  // glGenBuffers(1, &elementBufferObjectHanle);

  // GLuint vertixTriangleIndex[] = {
  //     0, 1, 2,
  //     2, 3, 0
  // };

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectHanle);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertixTriangleIndex), vertixTriangleIndex, GL_STATIC_DRAW);

  // Build, compile, and link our vertex and fragment shares into a program:
  GLuint defaultShaderProgram = ShaderUtil::BuildDefaultShaderProgram();
  glUseProgram(defaultShaderProgram); // Use shader program
  
  GLuint vertexArrayObjectHandle;
  glGenVertexArrays(1, &vertexArrayObjectHandle);
  glBindVertexArray(vertexArrayObjectHandle);  

  ShaderUtil::ConfigureDefaultShaderAttributes(defaultShaderProgram);

  // Create device object able to store texture in graphics card memory:
  GLuint textureObjectHandle;
  glGenTextures(1, &textureObjectHandle);
  glBindTexture(GL_TEXTURE_2D, textureObjectHandle); // Bind so we can apply operations to it
 
  // Load Texture: 
  // Black/white checkerboard
  int width, height;
  unsigned char* image = SOIL_load_image("resources/images/dark_wooden_crate.jpg", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  if(image == nullptr) {
    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    return false;
  }
  SOIL_free_image_data(image);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  while(windowShouldStayOpen()) {
      
      window.clearCurrentBuffer();

      // Draw
      glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

      window.swapBuffersAndCheckForEvents();
  } // Check if the ESC key was pressed or the window was closed

  return 0;
}

bool windowShouldStayOpen() {
  if (window.windowEspaceKeyHit()) return false;
  if (window.windowShouldClose()) return false;
  return true;
}


