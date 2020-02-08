#ifndef __MESH_INCLUDED__
#define __MESH_INCLUDED__

#include "window_manager.hpp"

class Mesh {
private:
    

public:
    int number_of_vertices;
    int number_of_indexes;
    float* vertices;
    GLuint* vertex_triangle_indeces;
    
    int sizeOfVertices();
    int sizeOfIndex();
    static Mesh Plane(float length, float width);
    static Mesh Cube(float size);
};

#endif 