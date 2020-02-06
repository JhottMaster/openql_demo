#ifndef __WINDOW_MANAGER_INCLUDED__
#define __WINDOW_MANAGER_INCLUDED__

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

class WindowManager {

public:
    GLFWwindow* window;
    int initialize(const char* windowName, int width, int height);
    bool windowShouldClose();
    bool windowEspaceKeyHit();
    bool windowKeyHit(int glfwKey);
    void swapBuffersAndCheckForEvents();
    void clearCurrentBuffer();
};

#endif 