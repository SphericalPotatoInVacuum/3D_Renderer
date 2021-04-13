#include <YAR/Object.hpp>

yar::Object::Object(glm::vec3 pos, glm::vec3 rot,
                    const std::vector<yar::Triangle>& triangles)
    : Entity(pos, rot), m_triangles(triangles) {}

yar::Object::Object(glm::vec3 pos, glm::vec3 rot,
                    std::initializer_list<yar::Triangle> list)
    : m_triangles(list) {}

const std::vector<yar::Triangle>& yar::Object::get_triangles() const {
  return m_triangles;
}
