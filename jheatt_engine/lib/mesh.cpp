#include "mesh.hpp"
using namespace glm;

float* Mesh::vertexList() { return vertices; }
GLuint* Mesh::indexList() { return vertex_triangle_indeces; }
int Mesh::indexCount() { return number_of_indexes; }
int Mesh::vertexCount() { return number_of_vertices; }

int Mesh::sizeOfVertices() {
  return sizeof(float) * number_of_vertices; 
}

int Mesh::sizeOfIndex() {
  return sizeof(GLuint) * number_of_indexes; 
}

Mesh::Mesh(Shader* shader) {
  MeshShader = shader;
  glGenVertexArrays(1, &vertex_array_object_handle);
}

void Mesh::Initialize() {
  if (initialized) return;
  glBindVertexArray(vertex_array_object_handle);

  // Create our vertex buffer on GPU and copy our vertex array to it:
  glGenBuffers(1, &vertex_buffer_object_handle); // Create device and assign to handle
  // Let's make it the active object so we can do stuff with it:
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_handle);
  glBufferData(GL_ARRAY_BUFFER, sizeOfVertices(), vertexList(), GL_STATIC_DRAW);

  // Create an element array
  glGenBuffers(1, &element_buffer_object_hanle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_hanle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndex(), indexList(), GL_STATIC_DRAW);

  // Configure usage of this shader:
  MeshShader->ConfigureAttributes();

  glBindVertexArray(0);
  initialized = true;
}

void Mesh::DrawMesh() {
  if (!initialized) Initialize();
  glBindVertexArray(vertex_array_object_handle);
  //glDrawElements(GL_TRIANGLES, cubeModel.indexCount(), GL_UNSIGNED_INT, 0);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount());
  glBindVertexArray(0);
}

Mesh* Mesh::Plane(Shader* shader, float length, float width) {
  Mesh* msh = new Mesh(shader);
  msh->number_of_vertices = 8 * 4;
  msh->vertices = new float[msh->number_of_vertices];
  float temp[] = {
      //  Position       Color               Texcoords
      //  X    Y    Z      R     G     B       U     V
      -length, 0.0f, width,   1.0f, 0.5f, 0.5f,   0.0f, 0.0f, // Top-left
      length, 0.0f, width,   0.5f, 1.0f, 0.5f,   1.0f, 0.0f, // Top-right
      length, 0.0f,-width,   0.5f, 0.5f, 1.0f,   1.0f, 1.0f, // Bottom-right
      -length, 0.0f,-width,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom-left
    };
  std::copy(temp, temp + msh->number_of_vertices, msh->vertices);

  // Create mappings of which vertex index are which points on triangles and bind to element buffer:
  msh->number_of_indexes = 6;
  msh->vertex_triangle_indeces = new GLuint[msh->number_of_indexes];
  
  GLuint temp_idx[] = {
      0, 1, 2, // Triangle 1
      2, 3, 0  // Triangle 2
  };
  std::copy(temp_idx, temp_idx + msh->number_of_indexes, msh->vertex_triangle_indeces);

  return msh;
}

Mesh* Mesh::Cube(Shader* shader, float size) {
  Mesh* msh = new Mesh(shader);
  msh->number_of_vertices = 8 * 6 * 6;

  size /= 2; // Must divide by 2 since size is from center
  msh->vertices = new float[msh->number_of_vertices];
  float temp[] = {
      //  Position       Color               Texcoords
      //  X    Y      Z      R     G     B      U     V
      -size, -size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      size, -size, -size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      size,  size, -size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      size,  size, -size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      -size,  size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -size, -size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

      -size, -size,  size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      size, -size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      size,  size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      size,  size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      -size,  size,  size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -size, -size,  size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

      -size,  size,  size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      -size,  size, -size,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      -size, -size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -size, -size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      -size, -size,  size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      -size,  size,  size,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

      size,  size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      size,  size, -size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      size, -size, -size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      size, -size, -size,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      size, -size,  size,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      size,  size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

      -size, -size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      size, -size, -size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      size, -size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      size, -size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      -size, -size,  size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      -size, -size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

      -size,  size, -size,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
      size,  size, -size,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
      size,  size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      size,  size,  size,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
      -size,  size,  size,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
      -size,  size, -size , 1.0f, 1.0f, 1.0f , 0.0f, 1.0f
    };
  std::copy(temp, temp + msh->number_of_vertices, msh->vertices);

  // Create mappings of which vertex index are which points on triangles and bind to element buffer:
  msh->number_of_indexes = 6 * 6;
  msh->vertex_triangle_indeces = new GLuint[msh->number_of_indexes];
  
  GLuint temp_idx[] = {
      0, 1, 2, 2, 3, 0,  // Side 1 (2 triangle faces)
      6, 7, 8, 8, 9, 6,  // Side 2
      12, 13, 14, 14, 6, 12,  // Side 3
      12, 2, 14, 14, 6, 12,  // Side 4
      14, 25, 7, 7, 6, 14,  // Side 5
      4, 2, 12, 12, 34, 4,  // Side 6
  };
  std::copy(temp_idx, temp_idx + msh->number_of_indexes, msh->vertex_triangle_indeces);

  return msh;
}

Mesh::~Mesh() {
  if (vertices != nullptr) delete[] vertices;
  if (vertex_triangle_indeces != nullptr) delete[] vertex_triangle_indeces;

  glDeleteBuffers(1, &element_buffer_object_hanle);
  glDeleteBuffers(1, &vertex_buffer_object_handle);
  glDeleteVertexArrays(1, &vertex_array_object_handle);
}
