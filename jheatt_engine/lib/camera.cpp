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
}

void Camera::windowManagerResized() {
  if (!AdjustToWindowDynamically) return;

  Width = _window->Width;
  Height = _window->Height;
}

void Camera::Draw(Shader* shader) {
  glViewport(XPos, YPos, Width, Height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  // View matrix:
  glm::mat4 view = glm::mat4(1.0f);
  // note that we're translating the scene in the reverse direction of where we want to move
  view = glm::translate(view, Position); 

  // Projection matrix:
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(FieldOfView), (float)Width / (float)Height, 0.1f, 100.0f);

  // Translation matrix:
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::translate(trans, Position);

  float timeValue = glfwGetTime();
  float sineWavValue = sin(timeValue);
  
  shader->UseShader(); // Activate shader before setting uniforms
  shader->SetFloatVariable("swap_amount", sineWavValue);

  shader->SetIntVariable("tex", 0); // or with shader class
  shader->SetIntVariable("tex2", 1); // or with shader class

  int viewLoc = glGetUniformLocation(shader->shaderProgram, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  int projectionLoc = glGetUniformLocation(shader->shaderProgram, "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


  for (Entity* currentEntity: _engine->Entities) {
    currentEntity->Render(shader);
  }
}

Camera::~Camera() {
  
}