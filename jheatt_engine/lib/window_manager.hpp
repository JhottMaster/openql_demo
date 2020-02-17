#ifndef __WINDOW_MANAGER_INCLUDED__
#define __WINDOW_MANAGER_INCLUDED__

#include "engine.hpp"

class Camera;
class Engine;

class WindowManager {
private:
    Engine* _engine;
    double deltaTime = 0.0f;	// Time between current frame and last frame
    double lastFrame = 0.0f; // Time of last frame
    double _last_mouse_x_scroll = 0.0f;
    double _last_mouse_y_scroll = 0.0f;
    bool _mouse_captured = false;

public:
    int Width, Height;
    double DeltaTime; // Used to multiply game actions by to create consistent motion
    double MouseXPosition = false;
    double MouseYPosition = false;
    GLFWwindow* windowHandle;
    
    std::vector<Camera *> Cameras;

    WindowManager(Engine* engine);

    int initialize(const char* windowName, int width, int height);
    
    bool windowShouldClose();
    bool windowEspaceKeyHit();
    bool windowKeyHit(int glfwKey);
    bool keyPressed(int glfwKey);
    bool keyReleased(int glfwKey);
    double mouseXScroll();
    double mouseYScroll();
    
    void swapBuffersAndCheckForEvents();
    void clearCurrentBuffer();
    void SendWindowManagerResizedMessage();
    void CalculateDeltaTime();
    void CaptureAndUseMouse();
    Camera* CreateCamera(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);

    static void windowResizeCallback(GLFWwindow * window, int width, int height);
    static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    ~WindowManager();
};

#endif 