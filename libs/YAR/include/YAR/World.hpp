#pragma once

#include <YAR/Object.hpp>
#include <memory>
#include <vector>

namespace yar {
class World {
 private:
  std::vector<Object *> m_objects;

 public:
  void add_object(Object *object);

  const std::vector<Object *> get_objects() const;
};
}  // namespace yar
