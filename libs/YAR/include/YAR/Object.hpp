#pragma once

#include <YAR/Entity.hpp>
#include <YAR/Triangle.hpp>
#include <glm/mat4x4.hpp>
#include <initializer_list>
#include <vector>

namespace yar {
class Object : public yar::Entity {
 public:
  Object(glm::vec3 pos, glm::vec3 rot, std::vector<yar::Triangle> triangles);
  Object(glm::vec3 pos, glm::vec3 rot,
         std::initializer_list<yar::Triangle> list);

  const std::vector<yar::Triangle>& get_triangles() const;

 private:
  std::vector<Triangle> m_triangles;
};

}  // namespace yar
