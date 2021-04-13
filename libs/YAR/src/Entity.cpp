#include <YAR/Entity.hpp>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

yar::Entity::Entity(glm::vec4 pos, glm::vec4 rot)
    : m_position(pos), m_rotation(rot) {
  m_transform_matrix = glm::translate(m_transform_matrix, -glm::vec3(pos));
  float angle = std::max(rot.x, std::max(rot.y, rot.z));
  m_transform_matrix =
      glm::rotate(m_transform_matrix, angle, glm::vec3(rot) / angle);
}

yar::Entity::Entity(glm::vec3 pos, glm::vec3 rot)
    : Entity(glm::vec4{pos.x, pos.y, pos.z, 1},
             glm::vec4{rot.x, rot.y, rot.z, 1}) {}

glm::mat4 yar::Entity::get_transform_matrix() const {
  return m_transform_matrix;
}

yar::Entity operator*(const glm::mat4 &mat) {
  return yar::Entity(mat * this->m_position, this->m_rotation);
}
