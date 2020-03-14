#ifndef __MESH_INCLUDED__
#define __MESH_INCLUDED__

#include "engine.hpp"
class Shader;
class TextureObject;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextureCoordinates;
};

struct MeshTexture {
    TextureObject* textureHandle;
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
    bool RenderWithIndices = true;

    std::vector<MeshTexture> textures;
    std::vector<Vertex> vertices;
    std::vector<GLuint> triangle_indices;
        
    JHEATT_ENGINE_API static Mesh* Plane(Shader* shader, float length = 1.0f, float width = 1.0f);
    JHEATT_ENGINE_API static Mesh* Cube(Shader* shader, float size = 1.0f);

    JHEATT_ENGINE_API void Initialize();
    void DrawMesh();
    JHEATT_ENGINE_API Mesh(Shader* shader);
    ~Mesh();
};

#endif 