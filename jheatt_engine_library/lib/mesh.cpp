#include "../headers/mesh.hpp"
using namespace glm;

int Mesh::sizeOfVertices() {
  return sizeof(Vertex) * vertices.size(); 
}

int Mesh::sizeOfElementIndexes() {
  return sizeof(GLuint) * triangle_indices.size(); 
}

Mesh::Mesh(Shader* shader) {
  MeshShader = shader;
}

void Mesh::Initialize() {
  if (initialized) return;
  // Create our buffer objects on GPU for GPU usage:
  glGenVertexArrays(1, &vertex_array_object_handle);
  glGenBuffers(1, &vertex_buffer_object_handle);
  glGenBuffers(1, &element_buffer_object_hanle); // Holds vertex index order
  
  // Make the vertex array object active so all changes following are saved to it
  glBindVertexArray(vertex_array_object_handle);
  
  // Switch to vertex buffer and fill it with vertices:
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_handle);    
  glBufferData(GL_ARRAY_BUFFER, sizeOfVertices(), &vertices[0], GL_STATIC_DRAW);
  
  // Switch to element buffer and fill it with vertex indices:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_hanle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfElementIndexes(), &triangle_indices[0], GL_STATIC_DRAW);

  // Configure usage of this shader:
  configureAttributes();

  // Unbind current vertex array object so no other changes are accidentally saved on it
  glBindVertexArray(0);
  initialized = true;
}

void Mesh::configureAttributes() {
	if (MeshShader->compilationFailed) {
		printf("WARNING: Attempting to configure attributes after failed shader compilation");
	}

  // First get argument positions & then we'll describe the data layout and format of each attribute.
  GLint positionIdx = glGetAttribLocation(MeshShader->shaderProgram, "position");
  GLint normalIdx = glGetAttribLocation(MeshShader->shaderProgram, "normal");
  GLint textureIdx = glGetAttribLocation(MeshShader->shaderProgram, "texcoord");

  // Vertex format & layout:
	glVertexAttribPointer(positionIdx, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(positionIdx);

  // Normals format & layout:
	glVertexAttribPointer(normalIdx, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(normalIdx);

  // Texture coordinates format & layout:
	glVertexAttribPointer(textureIdx, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoordinates));
	glEnableVertexAttribArray(textureIdx);
}

void Mesh::DrawMesh() {
  if (!initialized) Initialize();
    
  for(unsigned int i = 0; i < textures.size(); i++) {
    textures[i].textureHandle->UseTexture(MeshShader);
  }

  glBindVertexArray(vertex_array_object_handle);
  if (RenderWithIndices)
    glDrawElements(GL_TRIANGLES, triangle_indices.size() , GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  glBindVertexArray(0);
}

Mesh* Mesh::Plane(Shader* shader, float length, float width) {
  Mesh* msh = new Mesh(shader);
  //                                    Position                       Normal Data                   Texcoords
  //                                    X      Y      Z                X     Y      Z                U     V
  msh->vertices.push_back({ glm::vec3(-length, 0.0f, width), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f) }); // Top-left
  msh->vertices.push_back({ glm::vec3(length, 0.0f, width), glm::vec3(0.5f, 1.0f, 0.5f), glm::vec2(1.0f, 0.0f) }); // Top-right
  msh->vertices.push_back({ glm::vec3(length, 0.0f,-width), glm::vec3(0.5f, 0.5f, 1.0f), glm::vec2(1.0f, 1.0f) }); // Bottom-right
  msh->vertices.push_back({ glm::vec3(-length, 0.0f,-width), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }); // Bottom-left
    
  GLuint temp_idx[] = {
      0, 1, 2, // Triangle 1
      2, 3, 0  // Triangle 2
  };
  
  int temp_idx_size = sizeof(temp_idx)/sizeof(temp_idx[0]);
  for(int x = 0; x < temp_idx_size; x++) {
    msh->triangle_indices.push_back(temp_idx[x]);
  }

  return msh;
}

Mesh* Mesh::Cube(Shader* shader, float size) {
  size /= 2; // Must divide by 2 since size is from center

  Mesh* msh = new Mesh(shader);
  //                                    Position                       Normal Data                   Texcoords
  //                                    X      Y      Z                X     Y      Z                U     V
  msh->vertices.push_back({ glm::vec3(-size, -size, -size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size, -size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size, -size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size, -size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size,  size, -size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size, -size), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f) });

  msh->vertices.push_back({ glm::vec3(-size, -size,  size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size,  size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size,  size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size,  size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size,  size,  size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size,  size), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });

  msh->vertices.push_back({ glm::vec3(-size,  size,  size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(-size,  size, -size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size, -size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size, -size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size,  size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(-size,  size,  size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) });

  msh->vertices.push_back({ glm::vec3(size,  size,  size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size, -size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size, -size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size, -size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size,  size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size,  size), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) });

  msh->vertices.push_back({ glm::vec3(-size, -size, -size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size, -size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size,  size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size, -size,  size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size,  size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(-size, -size, -size), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });

  msh->vertices.push_back({ glm::vec3(-size,  size, -size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size, -size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size,  size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(size,  size,  size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(-size,  size,  size), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });
  msh->vertices.push_back({ glm::vec3(-size,  size, -size ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });
 
  // Now build out the element index:
  GLuint temp_idx[] = {
      0, 1, 2, 2, 4, 0,       // Side 1 (2 triangles per face)
      6, 7, 8, 8, 10, 6,      // Side 2
      12, 13, 14, 14, 6, 12,  // Side 3
      12, 13, 31, 31, 6, 12,  // Side 4 <- bad
      14, 25, 7, 7, 6, 14,    // Side 5
      4, 2, 12, 12, 34, 4,    // Side 6 <- bad
  };

  int temp_idx_size = sizeof(temp_idx)/sizeof(temp_idx[0]);
  for(int x = 0; x < temp_idx_size; x++) {
    msh->triangle_indices.push_back(temp_idx[x]);
  }

  msh->RenderWithIndices = false;
  return msh;
}

Mesh::~Mesh() {
  vertices.clear();
  vertices.shrink_to_fit();
  
  triangle_indices.clear();
  triangle_indices.shrink_to_fit();

  glDeleteBuffers(1, &element_buffer_object_hanle);
  glDeleteBuffers(1, &vertex_buffer_object_handle);
  glDeleteVertexArrays(1, &vertex_array_object_handle);
}
