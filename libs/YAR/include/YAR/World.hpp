#pragma once

#include <YAR/Object.hpp>
#include <memory>
#include <vector>

namespace yar {

/**
 * @brief The world object represents the 3D scene and holds the objects
 *
 */
class World {
 public:
  /**
   * @brief Add the object to the scene
   *
   * @param object Object to be added
   */
  void add_object(Object object);

  /**
   * @brief Get the objects in the scene
   *
   * @return const std::vector<Object>&
   */
  const std::vector<Object> &get_objects() const;

 private:
  std::vector<Object> m_objects;
};

}  // namespace yar
