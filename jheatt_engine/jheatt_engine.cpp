#define GLEW_STATIC

#include "lib/window_manager.hpp"
#include "lib/file_utils.hpp"
#include "lib/shader_util.hpp"
#include "lib/shader_program.hpp"

using namespace glm;

// Declarations
bool windowShouldStayOpen();

WindowManager window;

int main() {
    window.initialize("Open GL Demo", 1024, 768);

    GLuint vertexArrayObjectHandle = ShaderUtil::CreateAndBindVertexArray(1);

    float vertices[] = {
        //  Position       Color               Texcoords
        //  X      Y       R     G     B       U     V
            -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Top-left
            0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top-right
            0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // Bottom-right
            -0.5f,-0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom-left
    };

    GLuint vertexBufferObjectHandle = ShaderUtil::CreateAndBindVertexBufferObject(1, vertices, sizeof(vertices));

    GLuint vertixTriangleIndex[] = {
        0, 1, 2,
        2, 3, 0
    };
    GLuint elementBufferObjectHanle = ShaderUtil::CreateAndBindElementBufferObject(1, vertixTriangleIndex, sizeof(vertixTriangleIndex));

    // Build, compile, and link our vertex and fragment shares into a program:
    ShaderProgram defaultShaderProgram;
    if (!defaultShaderProgram.ConfigureDefaultShaderProgram()) return 0;;
    defaultShaderProgram.ConfigureDefaultShaderAttributes();

    GLuint textureObjectHandle = ShaderUtil::CreateAndBindTexture(1);
    if (!ShaderUtil::LoadRGBTexture("resources/images/dark_wooden_crate.jpg")) return 0;

    while (windowShouldStayOpen()) {
        window.clearCurrentBuffer();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffersAndCheckForEvents();
    }

    // Clean up/free memory:
    glDeleteTextures(1, &textureObjectHandle);
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



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
