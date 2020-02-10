#ifndef __WINDOW_MANAGER_INCLUDED__
#define __WINDOW_MANAGER_INCLUDED__

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

#include "camera.hpp"
#include "engine.hpp"
class Camera;
class Engine;

class WindowManager {
private:
    Engine* _engine;

public:
    int Width, Height;
    GLFWwindow* windowHandle;
    
    std::vector<Camera *> Cameras;

    WindowManager(Engine* engine);

    int initialize(const char* windowName, int width, int height);
    
    bool windowShouldClose();
    bool windowEspaceKeyHit();
    bool windowKeyHit(int glfwKey);
    
    void swapBuffersAndCheckForEvents();
    void clearCurrentBuffer();
    void SendWindowManagerResizedMessage();
    Camera* CreateCamera(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);

    static void windowResizeCallback(GLFWwindow * window, int width, int height);
};

#endif 