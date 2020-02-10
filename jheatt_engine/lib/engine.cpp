#include "engine.hpp"

// Global static pointer used to ensure a single instance of engine:
Engine* Engine::singletonInstance = NULL;  

Engine* Engine::GetOrCreateInstance() {
  if (!singletonInstance) singletonInstance = new Engine();
	return singletonInstance;
}

Engine::Engine() {
  
}

WindowManager* Engine::CreateWindow(const char* windowName, int width, int height) {
  WindowManager* pointer = new WindowManager(this);
  _windows.push_back(pointer);
  pointer->initialize(windowName, width, height);
  return pointer;
}

WindowManager* Engine::FindWindowManager(GLFWwindow * window) {
  for (WindowManager* currentManager: _windows) {
    if (currentManager->windowHandle == window) return currentManager;
  }
  fprintf(stderr, "Could not find GLFW window! (Searched among %i windows)\n", (int)_windows.size());
  return nullptr;
}

Engine::~Engine() {
  Entities.clear();
  Entities.shrink_to_fit();

  _windows.clear();
  _windows.shrink_to_fit();
}