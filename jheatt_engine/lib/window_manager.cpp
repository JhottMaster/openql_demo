#include "window_manager.hpp"

int WindowManager::initialize(const char* windowName, int width, int height) {
    // Setting this boolean is necessary to force GLEW to use a modern 
    // OpenGL method for checking if a function is available- it's also
    // required by the core profile (see `glfwWindowHint` below)
    glewExperimental = true;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initialize GLEW
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun)&WindowManager::windowResizeCallback);  

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return 0;
}

void WindowManager::windowResizeCallback(GLFWwindow * window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool WindowManager::windowEspaceKeyHit() {
    return windowKeyHit(GLFW_KEY_ESCAPE);
}

bool WindowManager::windowKeyHit(int glfwKey) {
    return (glfwGetKey(window, glfwKey) == GLFW_PRESS);
}

bool WindowManager::windowShouldClose() {
    return (glfwWindowShouldClose(window) != 0);
}

void WindowManager::swapBuffersAndCheckForEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowManager::clearCurrentBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}