#ifndef __MESH_INCLUDED__
#define __MESH_INCLUDED__

#include "engine.hpp"

class Mesh {
private:
    int number_of_vertices = 0;
    int number_of_indexes = 0;
    float* vertices = nullptr;
    GLuint* vertex_triangle_indeces = nullptr; 

public:
    int vertexCount();
    int indexCount();
    float* vertexList();
    GLuint* indexList();
    
    int sizeOfVertices();
    int sizeOfIndex();
    static Mesh* Plane(float length, float width);
    static Mesh* Cube(float size);

    void DrawMesh();
    ~Mesh();
};

#endif 