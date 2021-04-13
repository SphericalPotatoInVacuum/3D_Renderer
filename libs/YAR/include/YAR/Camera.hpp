#pragma once

#include <YAR/Entity.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace yar {

enum class ProjectionType { PERSPECTIVE, ORTHOGRAPHIC };

class Camera : yar::Entity {
 private:
  float m_fov = glm::radians(70.0f);
  float m_near = 1.0f;
  float m_far = 100.0f;
  float m_aspect_ratio = 1.0f;
  yar::ProjectionType m_projection_type = yar::ProjectionType::PERSPECTIVE;
  glm::mat4 m_projection_matrix =
      glm::perspective(m_fov, m_aspect_ratio, m_near, m_far);

 public:
  Camera();
  Camera(glm::vec4 pos, glm::vec4 rot, float fov, float near, float far,
         float aspect_ratio, yar::ProjectionType projection_type);
};

}  // namespace yar
