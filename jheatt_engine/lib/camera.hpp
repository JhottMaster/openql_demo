#ifndef __CAMERA_INCLUDED__
#define __CAMERA_INCLUDED__

#include "window_manager.hpp"

class Shader;
class Engine;
class WindowManager;

class Camera {
private:
  int initWindowManagerWidth, initWindowManagerHeight;
  Engine * _engine;
  WindowManager * _window;

public:
  bool AdjustToWindowDynamically;
  float FieldOfView;
  int Width, Height, XPos, YPos;
  glm::vec3 Position;
  glm::vec3 Rotation;

  Camera(WindowManager * window, Engine * engine);

  void Initialize(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);
  void windowManagerResized();
  void Draw(Shader* shader);

  ~Camera();
};

#endif 
