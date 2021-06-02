#pragma once

#include <YAR/Entity.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace yar {

class Camera : public yar::Entity {
 public:
  Camera(glm::vec3 pos, glm::vec3 rot, float fov, float near, float far,
         float aspect_ratio);
  glm::mat4 get_projection_matrix() const;
  float get_near() const;
  float get_far() const;

 private:
  float m_fov;
  float m_near;
  float m_far;
  float m_aspect_ratio;
  glm::mat4 m_projection_matrix;
};

}  // namespace yar
