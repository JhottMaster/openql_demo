#include "window_manager.hpp"
using namespace glm;

WindowManager window_manager;

bool windowShouldStayOpen() {
  if (window_manager.windowEspaceKeyHit()) return false;
  if (window_manager.windowShouldClose()) return false;
  return true;
}
 
int main() {

  
  window_manager.initialize("Open GL Demo", 1000, 768);
  
  while(windowShouldStayOpen()) {
      window_manager.clearCurrentBuffer();

      // Draw 

      window_manager.swapBuffersAndCheckForEvents();

  } // Check if the ESC key was pressed or the window was closed
}


