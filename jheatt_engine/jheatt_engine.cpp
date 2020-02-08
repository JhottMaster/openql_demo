#define GLEW_STATIC

#include "lib/window_manager.hpp"
#include "lib/file_utils.hpp"
#include "lib/shader_util.hpp"
#include "lib/shader.hpp"
#include "lib/texture_object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;


// Declarations
bool windowShouldStayOpen();

WindowManager window;

int main() {
    window.initialize("Open GL Demo", 1024, 768);
    
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

    // Create array of vertex:
    float vertices[] = {
        //  Position       Color               Texcoords
        //  X      Y       R     G     B       U     V
            -0.5f, 0.5f,   1.0f, 0.5f, 0.5f,   0.0f, 0.0f, // Top-left
            0.5f,  0.5f,   0.5f, 1.0f, 0.5f,   1.0f, 0.0f, // Top-right
            0.5f, -0.5f,   0.5f, 0.5f, 1.0f,   1.0f, 1.0f, // Bottom-right
            -0.5f,-0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom-left
    };

    // Create our vertex buffer on GPU and copy our vertex array to it:
    GLuint vertexBufferObjectHandle = ShaderUtil::CreateAndBindVertexBufferObject(1, vertices, sizeof(vertices));

    // Create mappings of which vertex index are which points on triangles and bind to element buffer:
    GLuint vertixTriangleIndex[] = {
        0, 1, 2, // Triangle 1
        2, 3, 0  // Triangle 2
    };
    GLuint elementBufferObjectHanle = ShaderUtil::CreateAndBindElementBufferObject(1, vertixTriangleIndex, sizeof(vertixTriangleIndex));

    TextureObject woodTexture = TextureObject("resources/images/dark_wooden_crate.jpg");
    TextureObject faceTexture = TextureObject("resources/images/awesomeface.png", 1);
    simpleShader.ConfigureAttributes();

    float timeValue, sineWavValue;

    while (windowShouldStayOpen()) {
        window.clearCurrentBuffer();
        
        timeValue = glfwGetTime();
        sineWavValue = sin(timeValue);
        
        simpleShader.UseShader(); // Activate shader before setting uniforms
        simpleShader.SetFloatVariable("swap_amount", sineWavValue);

        simpleShader.SetIntVariable("tex", 0); // or with shader class
        simpleShader.SetIntVariable("tex2", 1); // or with shader class

        mat4 trans = mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        unsigned int transformLoc = glGetUniformLocation(simpleShader.shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
                
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffersAndCheckForEvents();
    }

    // Clean up/free memory:
    glDeleteBuffers(1, &elementBufferObjectHanle);
    glDeleteBuffers(1, &vertexBufferObjectHandle);
    glDeleteVertexArrays(1, &vertexArrayObjectHandle);

    return 0;
}

// Check if the ESC key was pressed or the window was closed
bool windowShouldStayOpen() {
    if (window.windowEspaceKeyHit()) return false;
    if (window.windowShouldClose()) return false;
    return true;
}
