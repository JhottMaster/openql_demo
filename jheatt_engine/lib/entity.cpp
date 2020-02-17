#include "entity.hpp"

Entity::Entity(Mesh* mesh) {
  _mesh = mesh;
}

void Entity::Render(Shader* simpleShader) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, Position);
  model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

  int modelLoc = glGetUniformLocation(simpleShader->shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
          
  _mesh->DrawMesh();
}

Entity::~Entity() {
}