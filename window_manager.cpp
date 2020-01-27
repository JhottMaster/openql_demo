#include "window_manager.hpp"

int WindowManager::initialize(int width, int height) {
  // Initialise GLFW
  
  if( !glfwInit() )
  {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      return -1;
  }
  
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

  // Open a window and create its OpenGL context
  window = glfwCreateWindow( width, height, "Test Window", NULL, NULL);
  if( window == NULL ){
      fprintf( stderr, "Failed to open GLFW window.\n" );
      glfwTerminate();
      return -1;
  }
  glfwMakeContextCurrent(window); // Initialize GLEW
  glewExperimental=true; // Needed in core profile
  if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  return 0;
}

bool WindowManager::windowEspaceKeyHit() {
  return windowKeyHit(GLFW_KEY_ESCAPE);
}

bool WindowManager::windowKeyHit(int glfwKey) {
  return (glfwGetKey(window, glfwKey) == GLFW_PRESS);
}

bool WindowManager::windowShouldClose() {
  return (glfwWindowShouldClose(window) != 0);
}

bool WindowManager::swapBuffersAndCheckForEvents() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}