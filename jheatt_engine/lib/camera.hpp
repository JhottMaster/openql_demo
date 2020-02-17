#ifndef __CAMERA_INCLUDED__
#define __CAMERA_INCLUDED__

#include "engine.hpp"

class Shader;
class Engine;
class WindowManager;

class Camera {
private:
  int initWindowManagerWidth, initWindowManagerHeight;
  Engine * _engine;
  WindowManager * _window;
  glm::mat4 _view_matrix = glm::mat4(1.0f);
  glm::mat4 _projection_matrix = glm::mat4(1.0f);
  float _last_mouse_x = 0, _last_mouse_y = 0;

  void RecalculateProjectionMatrix();

public:
  bool IsOrthographic = false;
  bool AdjustToWindowDynamically = true;
  float MaxClipDistance = 100.0f;
  float MinClipDistance = 0.1f;
  float FieldOfView = 45.0f;
  float ShowcaseRadius = 10.0f;
  float ShowcaseAngle = 0.0f;

  int Width, Height, XPos, YPos;

  float CameraSpeed = 5.0f;
  glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

  Camera(WindowManager * window, Engine * engine);

  void CalculateBasicCameraMovement();
  void CalculateScrollZoom();
  void CalculateShowcaseCameraMovement(glm::vec3 center = glm::vec3(0.0, 0.0, 0.0));

  void Initialize(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);
  void windowManagerResized();
  void Draw(Shader* shader);

  ~Camera();
};

#endif 
