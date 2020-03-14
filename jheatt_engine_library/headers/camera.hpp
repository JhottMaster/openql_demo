#ifndef __CAMERA_INCLUDED__
#define __CAMERA_INCLUDED__

#include "engine.hpp"

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
  bool UseMouseToPan = true;
  bool IsOrthographic = false;
  bool AdjustToWindowDynamically = true;
  float MaxClipDistance = 100.0f;
  float MinClipDistance = 0.1f;
  float FieldOfView = 45.0f;
  float ShowcaseRadius = 10.0f;
  float ShowcaseAngle = 0.0f;
  glm::vec3 BackgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 AmbientLight = glm::vec3(1.0f, 1.0f, 1.0f);

  int Width, Height, XPos, YPos;

  float CameraSpeed = 5.0f;
  glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

  JHEATT_ENGINE_API Camera(WindowManager * window, Engine * engine);

  JHEATT_ENGINE_API void CalculateBasicCameraMovement();
  JHEATT_ENGINE_API void CalculateScrollZoom();
  JHEATT_ENGINE_API void CalculateShowcaseCameraMovement(glm::vec3 center = glm::vec3(0.0, 0.0, 0.0));

  void Initialize(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);
  void windowManagerResized();
  void UpdateShaderCameraScene(Shader *shader, bool ViewProjectionOnly);
  JHEATT_ENGINE_API void Draw();

  JHEATT_ENGINE_API ~Camera();
};

#endif 
