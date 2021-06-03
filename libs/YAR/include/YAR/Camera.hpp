#pragma once

#include <YAR/Entity.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace yar {

/**
 * @brief The camera class represents the virtual camera. The renderer will
 * render the scene from its point of view
 *
 */

class Camera : public yar::Entity {
 public:
  /**
   * @brief Construct a new Camera object
   *
   * @param pos Position of the camera
   * @param rot Rotation of the camera
   * @param fov Field of view in radians
   * @param near Distance to the near plane of the view frustum
   * @param far Distance to the far plane of the view frustum
   * @param aspect_ratio Aspect ratio width:height
   */
  Camera(glm::vec3 pos, glm::vec3 rot, float fov, float near, float far,
         float aspect_ratio);

  /**
   * @brief Get the projection matrix of this camera
   *
   * @return glm::mat4
   */
  glm::mat4 get_projection_matrix() const;

  /**
   * @brief Get the distance to the near plane
   *
   * @return float
   */
  float get_near() const;

  /**
   * @brief Get the distance to the far plane
   *
   * @return float
   */
  float get_far() const;

 private:
  float m_fov;
  float m_near;
  float m_far;
  float m_aspect_ratio;
  glm::mat4 m_projection_matrix;
};

}  // namespace yar
