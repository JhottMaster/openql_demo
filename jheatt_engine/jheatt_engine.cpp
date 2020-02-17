#define GLEW_STATIC

#include "lib/engine.hpp"
#include "lib/texture_object.hpp"

using namespace glm;


// Declarations
bool windowShouldStayOpen(WindowManager* window);

int main() {
    Engine& engine = *Engine::GetOrCreateInstance();
    WindowManager* window = engine.CreateWindow();

    Camera* camera = window->CreateCamera();
    camera->Position = glm::vec3(0.0f, 0.0f, -6.0f);

    // Setup shaders:
    Shader simpleShader("basic", "basic");
    if (simpleShader.compilationFailed) {
        printf("\nLast Error:\n%s\n", simpleShader.lastErrorCallStack);
        return 1;
    }

    /*
    A VAO that stores our vertex attribute configuration and which VBO to use. 
    Usually when we have multiple objects we want to draw, we first generate/
    configure all the VAOs (and thus the required VBO and attribute pointers) 
    and store those for later use. The moment we want to draw one of our objects,
    we take the corresponding VAO, bind it, then draw the object and unbind the 
    VAO again - in this case here I create the only VAO and immidiately bind to it:

    Create a vertex array object to store all the configuration on how to draw.
    */
    GLuint vertexArrayObjectHandle = ShaderUtil::CreateAndBindVertexArray(1);

    Mesh* cubeModel = Mesh::Cube(1);
    // Create our vertex buffer on GPU and copy our vertex array to it:
    GLuint vertexBufferObjectHandle = ShaderUtil::CreateAndBindVertexBufferObject(1, cubeModel->vertexList(), cubeModel->sizeOfVertices());
    GLuint elementBufferObjectHanle = ShaderUtil::CreateAndBindElementBufferObject(1, cubeModel->indexList(), cubeModel->sizeOfIndex());
    
    TextureObject woodTexture = TextureObject("resources/images/dark_wooden_crate.jpg");
    TextureObject faceTexture = TextureObject("resources/images/awesomeface.png", 1);
    simpleShader.ConfigureAttributes();

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

    glEnable(GL_DEPTH_TEST);
    
    while (windowShouldStayOpen(window)) {
        // Rotate each cube at different rates:
        for(unsigned int i = 0; i < 10; i++) {
            Entity* cubeEntity = engine.Entities[i];
            float angle = (i+1) * sin(glfwGetTime());
            cubeEntity->Rotation = glm::vec3(angle*50, angle*30, angle*75);
        }

        // Draw the camera scene:
        camera->Draw(&simpleShader);

        // Swap buffer:
        window->swapBuffersAndCheckForEvents();
    }

    // Clean up/free memory:
    glDeleteBuffers(1, &elementBufferObjectHanle);
    glDeleteBuffers(1, &vertexBufferObjectHandle);
    glDeleteVertexArrays(1, &vertexArrayObjectHandle);

    // Cleans up/frees all memory used by the engine:
    engine.Shutdown();
    return 0;
}

// Check if the ESC key was pressed or the window was closed
bool windowShouldStayOpen(WindowManager* window) {
    if (window->windowEspaceKeyHit()) return false;
    if (window->windowShouldClose()) return false;
    return true;
}
