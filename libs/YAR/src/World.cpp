#include <YAR/World.hpp>

void yar::World::add_object(yar::Object object) {
  m_objects.push_back(std::move(object));
}

const std::vector<yar::Object> &yar::World::get_objects() const {
  return m_objects;
}
