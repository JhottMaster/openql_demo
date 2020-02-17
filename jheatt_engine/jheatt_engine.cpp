#define GLEW_STATIC

#include "lib/engine.hpp"
#include "lib/texture_object.hpp"
#include <iomanip>

using namespace glm;


// Declarations
bool windowShouldStayOpen(WindowManager* window);
void SetTitle(WindowManager* window, Camera* cam);

int main() {
    Engine& engine = *Engine::GetOrCreateInstance();
    WindowManager* window = engine.CreateWindow();

    Camera* camera = window->CreateCamera();
    camera->Position = glm::vec3(0.0f, 0.0f, 6.0f);
    camera->AmbientLight = glm::vec3(0.2f, 0.2f, 0.2f);
    camera->BackgroundColor = camera->AmbientLight;

    // Light shader:
    Shader lightSourceShader("light_source", "light_source");
    if (lightSourceShader.compilationFailed) {
        printf("\nLast Error:\n%s\n", lightSourceShader.lastErrorCallStack);
        return 1;
    }

    // Setup shaders, mesh, & textures:
    // Normally also uses "textured" fragment, but using "light_receptive" fragment shader to develop lighting support:
    Shader simpleShader("textured", "light_receptive"); 
    if (simpleShader.compilationFailed) {
        printf("\nLast Error:\n%s\n", simpleShader.lastErrorCallStack);
        return 1;
    }

    Mesh* cubeModel = Mesh::Cube(&simpleShader);
    TextureObject woodTexture = TextureObject("resources/images/dark_wooden_crate.jpg");
    TextureObject faceTexture = TextureObject("resources/images/awesomeface.png", 1);
    simpleShader.UseShader(); // Activate shader before setting uniforms
    simpleShader.SetIntVariable("tex", 0);
    simpleShader.SetIntVariable("tex2", 1);

    // Build a bunch of cubes at various positions:
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    for(unsigned int i = 0; i < 10; i++) {
        Entity* cubeEntity = new Entity(cubeModel);
        cubeEntity->Position = cubePositions[i];
        engine.Entities.push_back(cubeEntity);
    }

    Entity* OmniLight = engine.AddLight(&lightSourceShader);
    OmniLight->Position = glm::vec3(0.0f, 0.0f, 3.0f);
    OmniLight->LightColor = glm::vec3(1.0f, 0.5f, 0.75f);

    // Enable depth testing so we write faces correctly:    
    glEnable(GL_DEPTH_TEST);

    float timeValue, sineWavValue;
    while (windowShouldStayOpen(window)) {
        window->CalculateDeltaTime();
        camera->CalculateBasicCameraMovement();
        camera->CalculateScrollZoom();
        SetTitle(window, camera);

        timeValue = glfwGetTime();
        sineWavValue = sin(timeValue);
        simpleShader.SetFloatVariable("swap_amount", sineWavValue);

        // Rotate each cube at different rates:
        for(unsigned int i = 0; i < 10; i++) {
            if (i < 5) continue; // Move only half the cubes
            Entity* cubeEntity = engine.Entities[i];
            float angle = (i+1) * sineWavValue * 0.1f;
            cubeEntity->Rotation = glm::vec3(angle*50, angle*30, angle*75);
        }
        
        // Change light position:
        OmniLight->Position.z = sineWavValue * 2.0f;
        OmniLight->Position.y = -sineWavValue * 2.0f;
        OmniLight->Position.x = cos(timeValue) * 2.0f;

        // Change light color
        OmniLight->LightColor.g = sineWavValue;

        // Draw the camera scene:
        camera->Draw();
        
        // Swap buffer
        window->swapBuffersAndCheckForEvents();
    }

    // Cleans up/frees all memory used by the engine:
    engine.Shutdown();
    return 0;
}

// Check if the ESC key was pressed or the window was closed
bool windowShouldStayOpen(WindowManager* window) {
    if (window->keyPressed(GLFW_KEY_ESCAPE)) return false;
    if (window->windowShouldClose()) return false;
    return true;
}

void AddVectorToStringStream(std::stringstream& fmt, glm::vec3 vect, bool position = true) {
    fmt << (position ? " X: " : " Roll: ");
    fmt << std::setprecision(3) << vect.x;
    fmt << (position ? ", Y: " : ", Yaw: ");
    fmt << std::setprecision(3) << vect.y;
    fmt << (position ? ", Z: " : ", Pitch: ");
    fmt << std::setprecision(3) << vect.z;
}

double last_title_set_time = 0;
void SetTitle(WindowManager* window, Camera* cam) {
    if ((glfwGetTime() - last_title_set_time) < 0.05) return;
    last_title_set_time = glfwGetTime();

    std::stringstream fmt;
    fmt << "Camera";
    AddVectorToStringStream(fmt, cam->Position);
    AddVectorToStringStream(fmt, cam->Rotation, false);
    window->SetTitle(fmt.str());
}