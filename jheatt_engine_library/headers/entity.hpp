#ifndef __ENTITY_INCLUDED__
#define __ENTITY_INCLUDED__

#include "engine.hpp"
#include "texture_object.hpp"

// Assimp for loading various types of models:
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
class Mesh;
class Camera;
class TextureObject;

enum class EntityLightType {
    NOT_A_LIGHT,
    OMNI_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

class Entity {
private:
    EntityLightType _light_type = EntityLightType::NOT_A_LIGHT;
    std::string _model_load_path;
    void ValidateLight(std::string calling_method);
    void CalculateLightConstants(float distance);
    bool processNode(aiNode *node, const aiScene *scene, Shader* shader);
    Mesh* processMesh(aiMesh *mesh, const aiScene *scene, Shader* shader);

    void loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureUsage typeName, Mesh* mesh);

public:
    std::vector<TextureObject*> Textures;
    std::vector<Mesh*> Meshes;
    glm::vec2 LightConstants = glm::vec2(0.7, 1.8);
    glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 LightDirection = glm::vec3(0.0f, -1.0f, 0.0f);

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float LightRadius = 30.0f;
    float SpotlightSpreadAngle = 15.0f;
    float SpotlightHardness = 0.9f;

    bool IsALight();
    JHEATT_ENGINE_API void SetLightType(EntityLightType type);
    
    JHEATT_ENGINE_API EntityLightType LightType();
    JHEATT_ENGINE_API Entity(EntityLightType = EntityLightType::NOT_A_LIGHT);
    JHEATT_ENGINE_API bool LoadModel(std::string path, Shader* shader);
    JHEATT_ENGINE_API void Render(Camera* camera);
    
    ~Entity();
};

#endif 