#include "window_manager.hpp"
using namespace glm;

WindowManager window_manager;
 
int main() {
  glewExperimental = true; // Needed for core profile
  window_manager.initialize(1000, 768);
  
  do {
      glClear( GL_COLOR_BUFFER_BIT );

      // Draw 

      window_manager.swapBuffersAndCheckForEvents();

  } // Check if the ESC key was pressed or the window was closed
  while(!window_manager.windowEspaceKeyHit() && !window_manager.windowShouldClose());

}