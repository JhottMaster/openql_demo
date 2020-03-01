#ifndef __MESH_INCLUDED__
#define __MESH_INCLUDED__

#include "engine.hpp"
class Shader;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextureCoordinates;
};

class Mesh {
private:
    bool initialized = false;
    
    GLuint vertex_array_object_handle;
    GLuint vertex_buffer_object_handle;
    GLuint element_buffer_object_hanle;    

    void configureAttributes();
    int sizeOfVertices();
    int sizeOfElementIndexes();

public:
    Shader* MeshShader;

    std::vector<Vertex> vertices;
    std::vector<GLuint> triangle_indices;
        
    static Mesh* Plane(Shader* shader, float length = 1.0f, float width = 1.0f);
    static Mesh* Cube(Shader* shader, float size = 1.0f);

    void Initialize();
    void DrawMesh();
    Mesh(Shader* shader);
    ~Mesh();
};

#endif 