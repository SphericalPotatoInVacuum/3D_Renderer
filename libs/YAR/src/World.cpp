#include <YAR/World.hpp>

void yar::World::add_object(yar::Object* object_ptr) {
  m_objects.push_back(object_ptr);
}

const std::vector<yar::Object*> yar::World::get_objects() const {
  return m_objects;
}
