#include "window_manager.hpp"
#include "file_utils.hpp"

using namespace glm;

// Declarations
bool windowShouldStayOpen();

WindowManager window;


int main() {

  
  window.initialize("Open GL Demo", 1000, 768);

  float vertices[] = {
      0.0f,  0.5f, // Vertex 1 (X, Y)
      0.5f, -0.5f, // Vertex 2 (X, Y)
      -0.5f, -0.5f  // Vertex 3 (X, Y)
  };

  // Create device object to store vertex data in graphics card memory:
  GLuint vertexBufferObjectHandle;
  glGenBuffers(1, &vertexBufferObjectHandle); // Create device and assign to handle

  // Let's make it the active object so we can do stuff with it:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Lets create a vertex shader object on the device to store shader program:
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  std::string contents = FileUtils::ReadString("shaders/2d_triangle.vert");
  char const * pointer = contents.c_str();
  glShaderSource(vertexShader, 1, &pointer, NULL);
  
  // Now let's compile it...
  glCompileShader(vertexShader);
  GLint status; // This will store compilation output result
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status); // Check result
  if (status != GL_TRUE) { 
    printf("Could not compile vertex shader! Callstack: \n"); 
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    printf("%s\n\nQuitting..", buffer);
    return 0; 
  }

  // Now create fragment shader object on the device:
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::string contents2 = FileUtils::ReadString("shaders/2d_triangle.frag");
  char const * pointer2 = contents2.c_str();
  glShaderSource(fragmentShader, 1, &pointer2, NULL);
  
  // Now let's compile it...
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status); // Check result
  if (status != GL_TRUE) { 
    printf("Could not compile fragment shader! Callstack: \n"); 
    char buffer[512];
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
    printf("%s\n\nQuitting..", buffer);
    return 0; 
  }
  
  // Now we'll need a complete program "pipeline"
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram); // Link it
  glUseProgram(shaderProgram); // Use it

  GLuint vertexArrayObjectHandle;
  glGenVertexArrays(1, &vertexArrayObjectHandle);
  glBindVertexArray(vertexArrayObjectHandle);  

  // Get the position of the "postition" argument in vertex shader:
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  // Describe the input type for posAttrib (vertices array)
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);
    
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


