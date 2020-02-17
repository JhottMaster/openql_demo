#ifndef __ENTITY_INCLUDED__
#define __ENTITY_INCLUDED__

#include "engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
class Mesh;

class Entity {
private:
    Mesh* _mesh;

public:
    glm::vec3 Position;
    glm::vec3 Rotation;

    Shader* MeshShader();
    Entity(Mesh* mesh);
    void Render();
    
    ~Entity();
};

#endif 