#pragma once

#include <YAR/Picture.hpp>
#include <array>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <initializer_list>

float edge_function(glm::vec2 vec, glm::vec2 point);

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

  template <typename T>
  T interpolate(T p0, T p1, T p2, glm::vec2 point) const {
    float den = edge_function(m_vecs[0], m_vecs[1]);
    float w0 = edge_function(m_vecs[1], point - glm::vec2(m_points[2])) / den;
    float w1 = edge_function(m_vecs[2], point - glm::vec2(m_points[0])) / den;
    float w2 = edge_function(m_vecs[0], point - glm::vec2(m_points[1])) / den;
    return p0 * w0 + p1 * w1 + p2 * w2;
  }

  void normalize();

  glm::vec4 get_bounding_box() const;
  bool is_inside(glm::vec2 point) const;
};

}  // namespace yar
