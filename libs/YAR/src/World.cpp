#include <YAR/World.hpp>

namespace yar {

void World::add_object(Object object) {
  m_objects.push_back(std::move(object));
}

const std::vector<Object> &World::get_objects() const {
  return m_objects;
}

}  // namespace yar
