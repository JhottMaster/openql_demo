#ifndef __ENTITY_INCLUDED__
#define __ENTITY_INCLUDED__

#include "engine.hpp"

// Assimp for loading various types of models:
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
class Mesh;
class Camera;

enum TextureType {
    DIFFUSE,
    SPECULAR
};

struct Texture {
    unsigned int id;
    TextureType type;
};

enum EntityLightType {
    NOT_A_LIGHT,
    OMNI_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

class Entity {
private:
    EntityLightType _light_type = NOT_A_LIGHT;
    void ValidateLight(std::string calling_method);
    void CalculateLightConstants(float distance);
    bool processNode(aiNode *node, const aiScene *scene, Shader* shader);
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene, Shader* shader);

public:
    std::vector<Texture> Textures;
    std::vector<Mesh*> Meshes;
    glm::vec2 LightConstants = glm::vec2(0.7, 1.8);
    glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 LightDirection = glm::vec3(0.0f, -1.0f, 0.0f);

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float LightRadius = 30.0f;
    float SpotlightSpreadAngle = 15.0f;
    float SpotlightHardness = 0.9f;

    bool IsALight();
    void SetLightType(EntityLightType type);
    
    EntityLightType LightType();
    Entity(EntityLightType = NOT_A_LIGHT);
    bool LoadModel(std::string path, Shader* shader);
    void Render(Camera* camera);
    
    ~Entity();
};

#endif 