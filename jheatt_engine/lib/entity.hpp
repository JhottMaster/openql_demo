#ifndef __ENTITY_INCLUDED__
#define __ENTITY_INCLUDED__

#include "mesh.hpp"
#include "shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
private:
    Mesh* _mesh;

public:
    glm::vec3 Position;
    glm::vec3 Rotation;

    Entity(Mesh* mesh);
    void Render(Shader* simpleShader);
};

#endif 