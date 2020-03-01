#include "entity.hpp"

Entity::Entity(EntityLightType light_type) {
  _light_type = light_type;
  if (light_type == OMNI_LIGHT || light_type == SPOT_LIGHT) CalculateLightConstants(LightRadius);
}

void Entity::Render(Camera* camera) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, Position);
  model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

  Shader* _currentMeshShader  = nullptr;
  for (Mesh* meshPointer: Meshes) {
    if (_currentMeshShader  == nullptr) {
      _currentMeshShader = meshPointer->MeshShader;
      bool entityIsLight = (_light_type != NOT_A_LIGHT);

      if (entityIsLight) _currentMeshShader->SetVec3Variable("lightColor", LightColor);    
      camera->UpdateShaderCameraScene(_currentMeshShader, entityIsLight);
      _currentMeshShader->SetFloatMatrixVariable("model", model);
    }
    meshPointer->DrawMesh();
  }
}

void Entity::SetLightType(EntityLightType type) {
  ValidateLight("SetLightType()");
  _light_type = type;
  if (type == OMNI_LIGHT || type == SPOT_LIGHT) CalculateLightConstants(LightRadius);
}

void Entity::CalculateLightConstants(float distance) {
  ValidateLight("CalculateLightConstants()");

  // Light attenuation constants to simulate a realistic lighting; curtesy of OGRE:
  // http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
  LightConstants = glm::vec2(0.7, 1.8);
  if (distance >= 7) LightConstants = glm::vec2(0.7f, 1.8f);
  if (distance >= 13) LightConstants = glm::vec2(0.35f, 0.44f);
  if (distance >= 20) LightConstants = glm::vec2(0.22f, 0.20f);
  if (distance >= 32) LightConstants = glm::vec2(0.14f, 0.07f);
  if (distance >= 50) LightConstants = glm::vec2(0.09f, 0.032f);
  if (distance >= 65) LightConstants = glm::vec2(0.07f, 0.017f);
  if (distance >= 100) LightConstants = glm::vec2(0.045f, 0.0075f);
  if (distance >= 160) LightConstants = glm::vec2(0.027f, 0.0028f);
  if (distance >= 200) LightConstants = glm::vec2(0.022f, 0.0019f);
  if (distance >= 325) LightConstants = glm::vec2(0.014f, 0.0007f);
  if (distance >= 600) LightConstants = glm::vec2(0.007f, 0.0002f);
  if (distance >= 3250) LightConstants = glm::vec2(0.0014f, 0.000007f);
}

void Entity::ValidateLight(std::string calling_method) {
  if (IsALight()) return;
  throw std::runtime_error("Unexpected call to " + calling_method + "on an entity that is not a light source.");
}

EntityLightType Entity::LightType() {
  return _light_type;
}

inline bool Entity::IsALight() {
  return (_light_type != NOT_A_LIGHT);
}

Entity::~Entity() {
  for (Mesh* meshPointer: Meshes) delete meshPointer;
  Meshes.clear();
  Meshes.shrink_to_fit();
}