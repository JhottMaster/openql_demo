#include "engine.hpp"

// Global static pointer used to ensure a single instance of engine:
Engine* Engine::singletonInstance = NULL;  

Engine* Engine::GetOrCreateInstance() {
  if (!singletonInstance) singletonInstance = new Engine();
	return singletonInstance;
}

Engine::Engine() {
  
}

Entity* Engine::AddLight(Shader* lightShader) {
  if (lightMesh == nullptr) lightMesh = Mesh::Cube(lightShader, 0.1f);
  Entity* lightPointer = new Entity(lightMesh, OMNI_LIGHT);
  Lights.push_back(lightPointer);
  return lightPointer;
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

void Engine::Shutdown() {
  delete Engine::singletonInstance;
  Engine::singletonInstance = nullptr;
}

Engine::~Engine() {
  for (Entity* entityPointer: Entities) delete entityPointer;
  Entities.clear();
  Entities.shrink_to_fit();

  for (Entity* lightEntityPointer: Lights) delete lightEntityPointer;
  Lights.clear();
  Lights.shrink_to_fit();
  if (lightMesh) delete lightMesh;

  for (WindowManager* windowPointer: _windows) delete windowPointer;
  _windows.clear();
  _windows.shrink_to_fit();
}