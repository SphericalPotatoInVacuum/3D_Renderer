#pragma once

#include <YAR/Object.hpp>
#include <vector>

namespace yar {
class World {
 private:
  std::vector<Object> m_objects;

 public:
  void add_object(const yar::Object object);

  std::vector<Triangle> get_triangles() const;
};
}  // namespace yar
