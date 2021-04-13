#include <YAR/World.hpp>

void yar::World::add_object(yar::Object object) {
  m_objects.push_back(object);
}

std::vector<yar::Triangle> yar::World::get_triangles() const {
  std::vector<yar::Triangle> triangles;

  for (const yar::Object& obj : m_objects) {
    glm::mat4 matrix = obj.get_transform_matrix();
    for (yar::Triangle t : obj.get_triangles()) {
      triangles.push_back(t);
    }
  }

  return triangles;
}
