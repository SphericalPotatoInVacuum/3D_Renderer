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
  std::array<glm::vec3, 3> m_vecs;
  std::array<glm::vec2, 3> m_lines;  // Ax + B = y -- A and B for all m_vecs
  yar::Color m_color;

  void update();

 public:
  Triangle(std::array<glm::vec4, 3> points);
  Triangle(std::initializer_list<glm::vec4> list);
  Triangle(std::array<glm::vec4, 3> points, Color color);
  Triangle(std::initializer_list<glm::vec4> list, Color color);

  yar::Triangle operator*(const glm::mat4 &mat) const;

  yar::Color get_color() const;
  std::array<glm::vec4, 3> get_points() const;
  std::array<float, 2> get_x(float y) const;
  std::array<float, 2> get_y(float x) const;
  float get_z(float x, float y) const;

  void normalize();

  glm::vec4 get_bounding_box() const;
  bool is_inside(glm::vec2 point) const;
};

}  // namespace yar
