#pragma once

#include <YAR/Entity.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace yar {

enum class ProjectionType { PERSPECTIVE, ORTHOGRAPHIC };

class Camera : public yar::Entity {
 public:
  Camera();
  Camera(glm::vec3 pos, glm::vec3 rot, float fov, float near, float far,
         float aspect_ratio);
  glm::mat4 get_projection_matrix() const;
  float get_near() const;
  float get_far() const;

 private:
  float m_fov = glm::radians(70.0f);
  float m_near = 0.1f;
  float m_far = 100.0f;
  float m_aspect_ratio = 1.0f;
  yar::ProjectionType m_projection_type = yar::ProjectionType::PERSPECTIVE;
  glm::mat4 m_projection_matrix =
      glm::perspective(m_fov, m_aspect_ratio, m_near, m_far);
};

}  // namespace yar
