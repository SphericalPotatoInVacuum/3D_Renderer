#pragma once

#include <YAR/Entity.hpp>
#include <YAR/Triangle.hpp>
#include <glm/mat4x4.hpp>
#include <initializer_list>
#include <vector>

namespace yar {

/**
 * @brief Object represents the 3D object in the scene
 *
 */
class Object : public yar::Entity {
 public:
  /**
   * @brief Construct a new Object object
   *
   * @param pos Position of the object
   * @param rot Rotation of the object
   * @param triangles Triangles that make up the 3D model of the object
   */
  Object(glm::vec3 pos, glm::vec3 rot, std::vector<yar::Triangle> triangles);

  /**
   * @brief Construct a new Object object
   *
   * @param pos Position of the object
   * @param rot Rotation of the object
   * @param list Triangles that make up the 3D model of the object
   */
  Object(glm::vec3 pos, glm::vec3 rot,
         std::initializer_list<yar::Triangle> list);

  /**
   * @brief Get the triangles that make up the 3D model of the object
   *
   * @return const std::vector<yar::Triangle>&
   */
  const std::vector<yar::Triangle>& get_triangles() const;

 private:
  std::vector<Triangle> m_triangles;
};

}  // namespace yar
