#include "camera.hpp"
#include "entity.hpp"
 
class Shader;

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
  RecalculateProjectionMatrix();
}

void Camera::RecalculateProjectionMatrix() {
  if(IsOrthographic) {
    _projection_matrix = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, MinClipDistance, MaxClipDistance);
  } else {
    float fov = glm::radians(FieldOfView);
    float aspectRatio = (float)Width / (float)Height;
    _projection_matrix =  glm::perspective(fov, aspectRatio, MinClipDistance, MaxClipDistance);
  }
}

void Camera::windowManagerResized() {
  if (!AdjustToWindowDynamically) return;

  Width = _window->Width;
  Height = _window->Height;
  RecalculateProjectionMatrix();
}

void Camera::Draw(Shader* shader) {
  glViewport(XPos, YPos, Width, Height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // View matrix:
  // (note that we're translating the scene in the reverse direction of where we want to move)
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, Position); 
  view = glm::rotate(view, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::rotate(view, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  view = glm::rotate(view, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

  shader->SetFloatMatrixVariable("view", view);
  shader->SetFloatMatrixVariable("projection", _projection_matrix);

  for (Entity* currentEntity: _engine->Entities) {
    currentEntity->Render(shader);
  }
}

Camera::~Camera() {
}