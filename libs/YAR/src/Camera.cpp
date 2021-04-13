#include <YAR/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

yar::Camera::Camera() {}

yar::Camera::Camera(glm::vec4 pos, glm::vec4 rot, float fov, float near,
                    float far, float aspect_ratio,
                    yar::ProjectionType projection_type)
    : Entity(pos, rot),
      m_fov(fov),
      m_near(near),
      m_far(far),
      m_aspect_ratio(aspect_ratio),
      m_projection_type(projection_type),
      m_projection_matrix(glm::perspective(fov, aspect_ratio, near, far)) {}
