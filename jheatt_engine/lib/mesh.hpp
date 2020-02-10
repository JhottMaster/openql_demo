#ifndef __MESH_INCLUDED__
#define __MESH_INCLUDED__

#include "window_manager.hpp"

#include <algorithm>
#include <iterator>

class Mesh {
private:
    int number_of_vertices;
    int number_of_indexes;
    float* vertices;
    GLuint* vertex_triangle_indeces; 

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
};

#endif 