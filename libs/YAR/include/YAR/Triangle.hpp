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

float get_signed_cp_length(glm::vec2 vec, glm::vec2 point);
class Triangle {
 public:
  Triangle(const glm::mat3x3& vertices, Color color);
  Triangle(const glm::mat3x3& vertices);
  Triangle(std::initializer_list<glm::vec3> list, Color color);
  Triangle(std::initializer_list<glm::vec3> list);

  yar::Color get_color() const;
  const glm::mat3x4& get_vertices() const;

  void cycle();

  float interpolate(float p0, float p1, float p2, glm::vec2 point) const {
    float den = get_signed_cp_length(m_vecs[0], m_vecs[1]);
    assert(("Triangles with zero surface area are not supported", den != 0.f));
    float w0 =
        get_signed_cp_length(m_vecs[1], point - glm::vec2(m_vertices[2])) / den;
    float w1 =
        get_signed_cp_length(m_vecs[2], point - glm::vec2(m_vertices[0])) / den;
    float w2 =
        get_signed_cp_length(m_vecs[0], point - glm::vec2(m_vertices[1])) / den;
    return p0 * w0 + p1 * w1 + p2 * w2;
  }

  Triangle& operator*=(const glm::mat4& mat);
  friend Triangle operator*(const glm::mat4& mat, const Triangle& tri);

  void project_to_3d();

  glm::vec4 get_bounding_box() const;

  bool is_inside(glm::vec2 point) const;

 private:
  glm::mat3x4 m_vertices;  // vertices of the triangle
  glm::mat3x3 m_vecs;
  yar::Color m_color;

  void update_vecs();
  glm::mat3x4 get_mat(std::initializer_list<glm::vec3> list);
};

}  // namespace yar
