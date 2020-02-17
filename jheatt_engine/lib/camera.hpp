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
  glm::mat4 _projection_matrix;
  void RecalculateProjectionMatrix();

public:
  bool IsOrthographic = false;
  bool AdjustToWindowDynamically = true;
  float MaxClipDistance = 100.0f;
  float MinClipDistance = 0.1f;
  float FieldOfView = 45.0f;

  int Width, Height, XPos, YPos;

  glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

  Camera(WindowManager * window, Engine * engine);

  void Initialize(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);
  void windowManagerResized();
  void Draw(Shader* shader);

  ~Camera();
};

#endif 
