#include "camera.hpp"
#include "entity.hpp"
 
class Shader;

Camera::Camera(WindowManager * window, Engine * engine) {
  _engine = engine;
  _window = window;
}

void Camera::Initialize(int width, int height, int x, int y, float fov) {
  glfwGetFramebufferSize(_window->windowHandle, &initWindowManagerWidth, &initWindowManagerHeight);
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

void Camera::CalculateBasicCameraMovement() {
  _window->CaptureAndUseMouse();

  if (_last_mouse_x == 0 && _last_mouse_y == 0) {
    // Handle case when first loading application (jarring mouse jump)
    _last_mouse_x = _window->MouseXPosition;
    _last_mouse_y = _window->MouseYPosition;
  }
  
  float xoffset = _window->MouseXPosition - _last_mouse_x;
  // Reversed since y-coordinates range from bottom to top:
  float yoffset = _last_mouse_y - _window->MouseYPosition;
  _last_mouse_x = _window->MouseXPosition;
  _last_mouse_y = _window->MouseYPosition;

  const float sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  Rotation.y += xoffset;
  Rotation.z += yoffset;

  // no "loops" when looking up or down:
  if(Rotation.z > 89.0f) Rotation.z = 89.0f;
  if(Rotation.z < -89.0f) Rotation.z = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(Rotation.y - 90.0f)) * cos(glm::radians(Rotation.z));
  direction.y = sin(glm::radians(Rotation.z));
  direction.z = sin(glm::radians(Rotation.y - 90.0f)) * cos(glm::radians(Rotation.z));
  
  glm::vec3 cameraFront = glm::normalize(direction);
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

  if (_window->keyPressed(GLFW_KEY_W))
    Position += CameraSpeed * cameraFront * (float)_window->DeltaTime;
  if (_window->keyPressed(GLFW_KEY_S))
    Position -= CameraSpeed * cameraFront * (float)_window->DeltaTime;
  if (_window->keyPressed(GLFW_KEY_A))
    Position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed * (float)_window->DeltaTime;
  if (_window->keyPressed(GLFW_KEY_D))
    Position += glm::normalize(glm::cross(cameraFront, cameraUp)) * CameraSpeed * (float)_window->DeltaTime;

  _view_matrix = glm::lookAt(Position, Position + cameraFront, cameraUp); 

  
}

void Camera::CalculateScrollZoom() {
  double mouse_y_scroll = _window->mouseYScroll();
  if (mouse_y_scroll != 0) {
    if(FieldOfView >= 1.0f && FieldOfView <= 50.0f)
      FieldOfView -= mouse_y_scroll;
    else if(FieldOfView <= 1.0f)
      FieldOfView = 1.0f;
    else if(FieldOfView >= 50.0f)
      FieldOfView = 50.0f;

    RecalculateProjectionMatrix();
  }
}

void Camera::CalculateShowcaseCameraMovement(glm::vec3 center) {
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

  if (_window->keyPressed(GLFW_KEY_W))
    ShowcaseRadius -= CameraSpeed * _window->DeltaTime;
  if (_window->keyPressed(GLFW_KEY_S))
    ShowcaseRadius += CameraSpeed * _window->DeltaTime;
  if (_window->keyPressed(GLFW_KEY_A))
    ShowcaseAngle -= CameraSpeed * 25.0f * _window->DeltaTime;
  if (_window->keyPressed(GLFW_KEY_D))
    ShowcaseAngle += CameraSpeed * 25.0f * _window->DeltaTime;

  float camX = sin(glm::radians(ShowcaseAngle)) * ShowcaseRadius;
  float camZ = cos(glm::radians(ShowcaseAngle)) * ShowcaseRadius;
  Position = glm::vec3(camX,  0.0f,  camZ);

  _view_matrix = glm::lookAt(Position, center, cameraUp);  
}

void Camera::Draw(Shader* shader) {
  glViewport(XPos, YPos, Width, Height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader->SetFloatMatrixVariable("view", _view_matrix);
  shader->SetFloatMatrixVariable("projection", _projection_matrix);

  for (Entity* currentEntity: _engine->Entities) {
    currentEntity->Render(shader);
  }
}

Camera::~Camera() {
}