#include <YAR/Entity.hpp>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

namespace yar {

Entity::Entity(glm::vec3 pos, glm::vec3 rot)
    : m_position(std::move(pos)),
      m_rotation(std::move(rot)),
      m_transform_matrix(make_transform_matrix()) {}

void Entity::set_position(const glm::vec3 &pos) {
  m_position = pos;
  m_transform_matrix = make_transform_matrix();
}

void Entity::set_rotation(const glm::vec3 &rot) {
  m_rotation = rot;
  m_transform_matrix = make_transform_matrix();
}

void Entity::move(glm::vec3 shift) {
  m_position += shift;
  m_transform_matrix = make_transform_matrix();
}

void Entity::rotate(glm::vec3 rot) {
  m_rotation += rot;
  m_transform_matrix = make_transform_matrix();
}

glm::mat4 Entity::get_transform_matrix() const {
  return m_transform_matrix;
}

glm::mat4 Entity::make_transform_matrix() const {
  glm::mat4 result;
  glm::mat4 rotation = glm::mat4(1.0f);
  rotation = glm::rotate(rotation, m_rotation.x, {1, 0, 0});
  rotation = glm::rotate(rotation, m_rotation.y, {0, 1, 0});
  rotation = glm::rotate(rotation, m_rotation.z, {0, 0, 1});
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
  result = translation * rotation;
  return result;
}

}  // namespace yar
