#pragma once

#include <glm/matrix.hpp>
#include <glm/vec4.hpp>

namespace yar {

class Entity {
 private:
  glm::vec4 m_position = {0, 0, 0, 1};
  glm::vec4 m_rotation = {0, 0, 0, 1};
  glm::mat4 m_transform_matrix = glm::mat4(1.0f);

 public:
  Entity(){};
  Entity(glm::vec3 position, glm::vec3 rotation);
  Entity(glm::vec4 position, glm::vec4 rotation);

  Entity operator*(const glm::mat4 &mat);

  glm::mat4 get_transform_matrix() const;
};

}  // namespace yar
