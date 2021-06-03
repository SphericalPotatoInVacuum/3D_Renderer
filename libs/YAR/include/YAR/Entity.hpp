#pragma once

#include <glm/matrix.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace yar {

/**
 * @brief Entity class is a base class for every object with position and
 * rotation (Object and Camera)
 *
 */
class Entity {
 public:
  /**
   * @brief Default constructor
   *
   */
  Entity() = default;

  /**
   * @brief Construct a new Entity object
   *
   * @param position Position of the entity
   * @param rotation Rotation of the entity
   */
  Entity(glm::vec3 position, glm::vec3 rotation);

  /**
   * @brief Set the position of the entity
   *
   * @param pos Position
   */
  void set_position(const glm::vec3 &pos);

  /**
   * @brief Set the rotation of the entity
   *
   * @param rot
   */
  void set_rotation(const glm::vec3 &rot);

  /**
   * @brief Shift the entity position
   *
   * @param shift The position will be shifted by shift
   */
  void move(glm::vec3 shift);

  /**
   * @brief Rotate the entity
   *
   * @param rot The rotation will be changed by rot
   */
  void rotate(glm::vec3 rot);

  /**
   * @brief Get the transform matrix of the entity
   *
   * @return glm::mat4
   */
  glm::mat4 get_transform_matrix() const;

 private:
  glm::vec3 m_position = {0, 0, 0};
  glm::vec3 m_rotation = {0, 0, 0};
  glm::mat4 m_transform_matrix = glm::mat4(1.0f);

  glm::mat4 make_transform_matrix() const;
};

}  // namespace yar
