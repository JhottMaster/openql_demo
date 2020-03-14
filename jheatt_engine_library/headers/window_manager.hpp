#ifndef __WINDOW_MANAGER_INCLUDED__
#define __WINDOW_MANAGER_INCLUDED__

#include "engine.hpp"

class Camera;
class Engine;

class WindowManager {
private:
    Engine* _engine;

    // Helpers for tracking keyboard and mouse state:
    int _last_key_pressed = 0;
    double _last_key_press_time = 0.0;
    int _last_mouse_button_pressed = -1;
    double _last_mouse_button_press_time = 0.0;
    
    double deltaTime = 0.0f; // Time between current frame and last frame
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

    JHEATT_ENGINE_API WindowManager(Engine* engine);

    JHEATT_ENGINE_API int initialize(const char* windowName, int width, int height);
    
    JHEATT_ENGINE_API bool windowShouldClose();
    JHEATT_ENGINE_API bool windowEspaceKeyHit();
    JHEATT_ENGINE_API bool windowKeyHit(int glfwKey);
    JHEATT_ENGINE_API bool mouseButtonPressRelease(int glfwMouseButton, double button_press_duration = 0.1f);
    JHEATT_ENGINE_API bool keyPressRelease(int glfwKey, double key_press_duration = 0.1f);
    JHEATT_ENGINE_API bool keyPressed(int glfwKey);
    JHEATT_ENGINE_API bool keyReleased(int glfwKey);
    JHEATT_ENGINE_API bool mouseButtonPressed(int glfwMouseButton);
    JHEATT_ENGINE_API double mouseXScroll();
    JHEATT_ENGINE_API double mouseYScroll();
    
    JHEATT_ENGINE_API void SetTitle(const std::string &title);
    JHEATT_ENGINE_API void swapBuffersAndCheckForEvents();
    JHEATT_ENGINE_API void clearCurrentBuffer();
    JHEATT_ENGINE_API void SendWindowManagerResizedMessage();
    JHEATT_ENGINE_API void CalculateDeltaTime();
    JHEATT_ENGINE_API void CaptureAndUseMouse();
    JHEATT_ENGINE_API void ReleaseMouse();
    JHEATT_ENGINE_API Camera* CreateCamera(int width = 0, int height = 0, int x = 0, int y = 0, float fov = 45.0f);

    static void windowResizeCallback(GLFWwindow* window, int width, int height);
    static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    ~WindowManager();
};

#endif 