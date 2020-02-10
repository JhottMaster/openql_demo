#ifndef __ENGINE_INCLUDED__
#define __ENGINE_INCLUDED__

#include <vector>
#include "window_manager.hpp"

class WindowManager;
class Mesh;

class Engine {
private:
  // Make this a singleton:
  static Engine* singletonInstance;
  Engine(Engine const&){};          // Copy constructor
  Engine();                         // Default constructor

  std::vector<WindowManager *> _windows;
  
public:
  static Engine* GetOrCreateInstance(); // How we get our singleton engine
  std::vector<Mesh *> Meshes;

  WindowManager* CreateWindow(const char* windowName = "Jheatt Engine", int width = 1024, int height = 768);
  WindowManager* FindWindowManager(GLFWwindow * window);

  ~Engine();
};

#endif 
