#ifndef __WINDOW_MANAGER_INCLUDED__
#define __WINDOW_MANAGER_INCLUDED__

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

    ~WindowManager();
};

#endif 