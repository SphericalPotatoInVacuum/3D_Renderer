#include <YAR/Object.hpp>

namespace yar {

Object::Object(glm::vec3 pos, glm::vec3 rot, std::vector<Triangle> triangles)
    : Entity(pos, rot), m_triangles(std::move(triangles)) {}

Object::Object(glm::vec3 pos, glm::vec3 rot,
               std::initializer_list<Triangle> list)
    : Entity(pos, rot), m_triangles(list) {}

const std::vector<Triangle>& Object::get_triangles() const {
  return m_triangles;
}

}  // namespace yar
