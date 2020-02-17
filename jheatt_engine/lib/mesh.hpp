#ifndef __MESH_INCLUDED__
#define __MESH_INCLUDED__

#include "engine.hpp"
class Shader;

class Mesh {
private:
    bool initialized = false;
    
    GLuint vertex_array_object_handle;
    GLuint vertex_buffer_object_handle;
    GLuint element_buffer_object_hanle;

    int number_of_vertices = 0;
    int number_of_indexes = 0;
    float* vertices = nullptr;
    GLuint* vertex_triangle_indeces = nullptr; 

public:
    int vertexCount();
    int indexCount();
    float* vertexList();
    GLuint* indexList();
    Shader* MeshShader;
    
    int sizeOfVertices();
    int sizeOfIndex();
    static Mesh* Plane(Shader* shader, float length = 1.0f, float width = 1.0f);
    static Mesh* Cube(Shader* shader, float size = 1.0f);

    void Initialize();
    void DrawMesh();
    Mesh(Shader* shader);
    ~Mesh();
};

#endif 