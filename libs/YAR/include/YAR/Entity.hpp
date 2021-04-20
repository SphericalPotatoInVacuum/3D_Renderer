#pragma once

#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace yar {

class Entity {
 private:
  glm::vec3 m_position = {0, 0, 0};
  glm::vec3 m_rotation = {0, 0, 0};
  glm::mat4 m_transform_matrix = glm::mat4(1.0f);
  std::string m_name = "bare entity";

  void update_matrices();

 public:
  Entity(){};
  Entity(glm::vec3 position, glm::vec3 rotation);

  void set_position(glm::vec3 pos);
  void set_rotation(glm::vec3 rot);

  void move(glm::vec3 shift);
  void rotate(glm::vec3 rot);

  glm::mat4 get_transform_matrix() const;
};

}  // namespace yar
