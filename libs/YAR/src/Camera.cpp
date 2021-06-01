#include <YAR/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

yar::Camera::Camera() {}

yar::Camera::Camera(glm::vec3 pos, glm::vec3 rot, float fov, float near,
                    float far, float aspect_ratio)
    : Entity(pos, rot),
      m_fov(fov),
      m_near(near),
      m_far(far),
      m_aspect_ratio(aspect_ratio),
      m_projection_matrix(glm::perspective(fov, aspect_ratio, near, far)) {}

glm::mat4 yar::Camera::get_projection_matrix() const {
  return m_projection_matrix;
}

float yar::Camera::get_near() const {
  return m_near;
}

float yar::Camera::get_far() const {
  return m_far;
}
