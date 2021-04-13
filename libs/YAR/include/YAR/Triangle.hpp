#pragma once

#include <YAR/Picture.hpp>
#include <array>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <initializer_list>

namespace yar {

class Triangle {
 private:
  std::array<glm::vec4, 3> m_points;
  std::array<glm::vec2, 3> m_vecs;
  glm::vec4 m_norm;
  yar::Color m_color;

 public:
  Triangle(std::array<glm::vec4, 3> points);
  Triangle(std::initializer_list<glm::vec4> list);

  yar::Triangle operator*(const glm::mat4 &mat);

  yar::Color get_color() const;

  glm::vec4 get_bounding_box() const;
  bool is_inside(glm::vec2 point) const;
};

}  // namespace yar
