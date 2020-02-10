#include "camera.hpp"
#include "mesh.hpp"

Camera::Camera(WindowManager * window, Engine * engine) {
  _engine = engine;
  _window = window;
}

void Camera::Initialize(int width, int height, int x, int y, float fov) {
  glfwGetWindowSize(_window->windowHandle, &initWindowManagerWidth, &initWindowManagerHeight);
  width == 0 ? Width = initWindowManagerWidth : Width = width;
  height == 0 ? Height = initWindowManagerHeight : Width = height;
  
  XPos = x;
  YPos = y;
  FieldOfView = fov;
  AdjustToWindowDynamically = true;
  glViewport(0, 0, width, height);
}

void Camera::windowManagerResized() {
  if (!AdjustToWindowDynamically) return;

  Width = _window->Width;
  Height = _window->Height;
}

void Camera::Draw() {
  glViewport(XPos, YPos, Width, Height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (Mesh* currentMesh: _engine->Meshes) {
    currentMesh->Render();
  }
}

Camera::~Camera() {
  
}