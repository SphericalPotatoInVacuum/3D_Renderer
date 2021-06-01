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
 public:
  Triangle(const glm::mat3x3& vertices);
  Triangle(std::initializer_list<glm::vec3> list);
  Triangle(const glm::mat3x3& vertices, Color color);
  Triangle(std::initializer_list<glm::vec3> list, Color color);

  yar::Color get_color() const;
  glm::mat3x4 get_vertices() const;

  void cycle();

  template <typename T>
  T interpolate(T p0, T p1, T p2, glm::vec2 point) const {
    float den = edge_function(m_vecs[0], m_vecs[1]);
    float w0 = edge_function(m_vecs[1], point - glm::vec2(m_vertices[2])) / den;
    float w1 = edge_function(m_vecs[2], point - glm::vec2(m_vertices[0])) / den;
    float w2 = edge_function(m_vecs[0], point - glm::vec2(m_vertices[1])) / den;
    return p0 * w0 + p1 * w1 + p2 * w2;
  }

  Triangle operator*(const glm::mat4& mat) const;

  void project_to_3d();

  glm::vec4 get_bounding_box() const;
  bool is_inside(glm::vec2 point) const;

 private:
  glm::mat3x4 m_vertices;  // vertices of the triangle
  glm::mat3x3 m_vecs;
  yar::Color m_color;

  void update();
};

Triangle operator*(const glm::mat4& mat, const Triangle tri);
}  // namespace yar
