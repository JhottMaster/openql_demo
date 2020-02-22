#ifndef __ENTITY_INCLUDED__
#define __ENTITY_INCLUDED__

#include "engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
class Mesh;

enum EntityLightType {
    NOT_A_LIGHT,
    OMNI_LIGHT,
    DIRECTIONAL_LIGHT
};

class Entity {
private:
    Mesh* _mesh;

public:
    EntityLightType LightType = NOT_A_LIGHT;
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 LightDirection = glm::vec3(0.0f, -1.0f, 0.0f);
    float LightRadius = 15.0f;

    Shader* MeshShader();
    Entity(Mesh* mesh);
    void Render();
    
    ~Entity();
};

#endif 