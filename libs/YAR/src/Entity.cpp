#include <YAR/Entity.hpp>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

yar::Entity::Entity(glm::vec3 pos, glm::vec3 rot)
    : m_position(pos), m_rotation(rot) {
  update_matrices();
}

glm::mat4 yar::Entity::get_transform_matrix() const {
  return m_transform_matrix;
}

void yar::Entity::set_position(glm::vec3 pos) {
  m_position = pos;
  update_matrices();
}

void yar::Entity::set_rotation(glm::vec3 rot) {
  m_rotation = rot;
  update_matrices();
}

void yar::Entity::move(glm::vec3 shift) {
  m_position += shift;
  update_matrices();
}

void yar::Entity::rotate(glm::vec3 rot) {
  m_rotation += rot;
  update_matrices();
}

void yar::Entity::update_matrices() {
  glm::mat4 rotation = glm::mat4(1.0f);
  rotation = glm::rotate(rotation, m_rotation.x, {1, 0, 0});
  rotation = glm::rotate(rotation, m_rotation.y, {0, 1, 0});
  rotation = glm::rotate(rotation, m_rotation.z, {0, 0, 1});
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
  m_transform_matrix = translation * rotation;
}
