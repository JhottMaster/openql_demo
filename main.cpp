#include "window_manager.hpp"
using namespace glm;

WindowManager window_manager;

bool windowShouldStayOpen() {
  if (window_manager.windowEspaceKeyHit()) return false;
  if (window_manager.windowShouldClose()) return false;
  return true;
}
 
int main() {
  glewExperimental = true; // Needed for core profile
  window_manager.initialize(1000, 768);
  
  while(windowShouldStayOpen()) {
      glClear( GL_COLOR_BUFFER_BIT );

      // Draw 

      window_manager.swapBuffersAndCheckForEvents();

  } // Check if the ESC key was pressed or the window was closed
}


