#include "window_manager.hpp"

WindowManager::WindowManager(Engine* engine) {
    _engine = engine;
}

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
    windowHandle = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (windowHandle == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(windowHandle, (GLFWframebuffersizefun)&WindowManager::windowResizeCallback);  
    glfwMakeContextCurrent(windowHandle); // Initialize GLEW
    glfwGetFramebufferSize(windowHandle, &Width, &Height);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    lastFrame = glfwGetTime();

    return 0;
}

Camera* WindowManager::CreateCamera(int width, int height, int x, int y, float fov) {
    Camera* new_camera = new Camera(this, _engine);
    Cameras.push_back(new_camera) ;
    new_camera->Initialize(width, height, x, y, fov);
    return new_camera;
}

void WindowManager::SetTitle(const std::string &title) {
    glfwSetWindowTitle(windowHandle, title.c_str());
}

void WindowManager::windowResizeCallback(GLFWwindow * window, int width, int height) {
    Engine* engine = Engine::GetOrCreateInstance();
    WindowManager* currentManger = engine->FindWindowManager(window);
    if (currentManger == nullptr) return;

    currentManger->Width = width;
    currentManger->Height = height;
    currentManger->SendWindowManagerResizedMessage();
}

void WindowManager::mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
    Engine* engine = Engine::GetOrCreateInstance();
    WindowManager* currentManger = engine->FindWindowManager(window);
    if (currentManger == nullptr) return;

    currentManger->MouseXPosition = xpos;
    currentManger->MouseYPosition = ypos;
}

void WindowManager::SendWindowManagerResizedMessage() {
    for (Camera* currentCamera: Cameras) currentCamera->windowManagerResized();
}

void WindowManager::CaptureAndUseMouse() {
    if (_mouse_captured) return;
    glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(windowHandle, WindowManager::mousePositionCallback);  
    glfwSetScrollCallback(windowHandle, mouseScrollCallback);
    _mouse_captured = true;
}

void WindowManager::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine* engine = Engine::GetOrCreateInstance();
    WindowManager* currentManger = engine->FindWindowManager(window);
    if (currentManger == nullptr) return;

    currentManger->_last_mouse_x_scroll = xoffset;
    currentManger->_last_mouse_y_scroll = yoffset;
}

double WindowManager::mouseXScroll() {
    double ret = _last_mouse_x_scroll;
    _last_mouse_x_scroll = 0.0f;
    return ret;
}

double WindowManager::mouseYScroll() {
    double ret = _last_mouse_y_scroll;
    _last_mouse_y_scroll = 0.0f;
    return ret;
}

bool WindowManager::keyPressed(int key) {
    return (glfwGetKey(windowHandle, key) == GLFW_PRESS);
}

bool WindowManager::keyReleased(int key) {
    return (glfwGetKey(windowHandle, key) == GLFW_RELEASE);
}

bool WindowManager::windowShouldClose() {
    return (glfwWindowShouldClose(windowHandle) != 0);
}

void WindowManager::swapBuffersAndCheckForEvents() {
    glfwSwapBuffers(windowHandle);
    glfwPollEvents();  
}

void WindowManager::CalculateDeltaTime() {
    double currentFrame = glfwGetTime();
    DeltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame; 
    //DeltaTime = (float) 0.1f;
}

void WindowManager::clearCurrentBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

WindowManager::~WindowManager() {
    for (Camera* cameraPointer: Cameras) delete cameraPointer;
    Cameras.clear();
    Cameras.shrink_to_fit();
}