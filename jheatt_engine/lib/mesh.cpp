#include "mesh.hpp"

Mesh Mesh::Plane(float length, float width) {
  Mesh msh;
  msh.number_of_vertices = 8 * 4;
  msh.vertices = new float[msh.number_of_vertices] {
      //  Position       Color               Texcoords
      //  X    Y    Z      R     G     B       U     V
      -0.5f, 0.5f, 0.0f,   1.0f, 0.5f, 0.5f,   0.0f, 0.0f, // Top-left
      0.5f,  0.5f, 0.0f,   0.5f, 1.0f, 0.5f,   1.0f, 0.0f, // Top-right
      0.5f, -0.5f, 0.0f,   0.5f, 0.5f, 1.0f,   1.0f, 1.0f, // Bottom-right
      -0.5f,-0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom-left
    };

  // Create mappings of which vertex index are which points on triangles and bind to element buffer:
  msh.number_of_indexes = 6;
  msh.vertex_triangle_indeces = new GLuint[msh.number_of_indexes] {
      0, 1, 2, // Triangle 1
      2, 3, 0  // Triangle 2
  };
  return msh;
}

Mesh Mesh::Cube(float size) {
  Mesh msh;
  msh.number_of_vertices = 8 * 6 * 6;
  msh.vertices = new float[msh.number_of_vertices] {
      //  Position       Color               Texcoords
      //  X    Y      Z      R     G     B      U     V
      -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f , 1.0f, 1.0f, 1.0f , 0.0f, 1.0f
    };

  // Create mappings of which vertex index are which points on triangles and bind to element buffer:
  msh.number_of_indexes = 6 * 6;
  msh.vertex_triangle_indeces = new GLuint[msh.number_of_indexes] {
      0, 1, 2, 2, 3, 0,  // Side 1 (2 triangle faces)
      6, 7, 8, 8, 9, 6,  // Side 2
      12, 13, 14, 14, 6, 12,  // Side 3
      12, 2, 14, 14, 6, 12,  // Side 4
      14, 25, 7, 7, 6, 14,  // Side 5
      4, 2, 12, 12, 34, 4,  // Side 6
  };
  return msh;
}

int Mesh::sizeOfVertices() {
  return sizeof(float) * number_of_vertices; 
}

int Mesh::sizeOfIndex() {
  return sizeof(GLuint) * number_of_indexes; 
}