#define GLEW_STATIC

#include "lib/window_manager.hpp"
#include "lib/file_utils.hpp"
#include "lib/shader_util.hpp"
#include "lib/shader.hpp"
#include "lib/texture_object.hpp"
#include "lib/mesh.hpp"

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

    Mesh plane = Mesh::Cube(1);

    // Create our vertex buffer on GPU and copy our vertex array to it:
    GLuint vertexBufferObjectHandle = ShaderUtil::CreateAndBindVertexBufferObject(1, plane.vertices, plane.sizeOfVertices());
    GLuint elementBufferObjectHanle = ShaderUtil::CreateAndBindElementBufferObject(1, plane.vertex_triangle_indeces, plane.sizeOfIndex());

    TextureObject woodTexture = TextureObject("resources/images/dark_wooden_crate.jpg");
    TextureObject faceTexture = TextureObject("resources/images/awesomeface.png", 1);
    simpleShader.ConfigureAttributes();

    float timeValue, sineWavValue;

    // Model matrix:
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

    // View matrix:
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    // Projection matrix:
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

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
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::rotate(model, sineWavValue * glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        int modelLoc = glGetUniformLocation(simpleShader.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(simpleShader.shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(simpleShader.shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
                
        //glDrawElements(GL_TRIANGLES, plane.number_of_indexes, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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
