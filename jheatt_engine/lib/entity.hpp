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
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

class Entity {
private:
    Mesh* _mesh;
    EntityLightType _light_type = NOT_A_LIGHT;
    void ValidateLight(std::string calling_method);
    void CalculateLightConstants(float distance);

public:
    glm::vec2 LightConstants = glm::vec2(0.7, 1.8);
    glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 LightDirection = glm::vec3(0.0f, -1.0f, 0.0f);

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float LightRadius = 30.0f;
    float SpotlightSpreadAngle = 15.0f;
    float SpotlightHardness = 0.85f;

    bool IsALight();
    void SetLightType(EntityLightType type);
    
    EntityLightType LightType();
    Shader* MeshShader();
    Entity(Mesh* mesh, EntityLightType = NOT_A_LIGHT);
    void Render();
    
    ~Entity();
};

#endif 