#ifndef __ENGINE_INCLUDED__
#define __ENGINE_INCLUDED__

#define GLEW_STATIC

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

// OpenGL related includes:
#include <GL/glew.h> // Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Ordered Engine Includes
// First, include most basic building blocks:
#include "shader_util.hpp"
#include "shader.hpp"
#include "mesh.hpp"

// Now build out the entities that use them:
#include "entity.hpp"
#include "camera.hpp"
#include "window_manager.hpp"

class WindowManager;
class Entity;
class Mesh;

class Engine {
private:
  // Make this a singleton:
  static Engine* singletonInstance;
  Engine(Engine const&){};          // Copy constructor
  Engine();                         // Default constructor

  std::vector<WindowManager *> _windows;
  Mesh* lightMesh = nullptr;
  
public:
  static Engine* GetOrCreateInstance(); // How we get our singleton engine
  std::vector<Entity *> Entities;
  std::vector<Entity *> Lights;

  WindowManager* CreateWindow(const char* windowName = "Jheatt Engine", int width = 1024, int height = 768);
  WindowManager* FindWindowManager(GLFWwindow* window);
  Entity* AddLight(Shader* lightShader);

  void Shutdown();
  ~Engine();
};

#endif 
