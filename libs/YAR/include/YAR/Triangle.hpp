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

/**
 * @brief Get the signed cross product length between vector AB and AP for
 * vector AB and point P
 *
 * @param vec Vector AB
 * @param point Point P
 * @return float
 */
float get_signed_cp_length(glm::vec2 vec, glm::vec2 point);

/**
 * @brief Triangle class represents the 3D triangle
 *
 */
class Triangle {
 public:
  /**
   * @brief Construct a new Triangle object
   *
   * @param vertices Vertices of the triangle (in counter-clockwise order)
   * @param color Color of the triangle
   */
  Triangle(const glm::mat3x3& vertices, Color color);

  /**
   * @brief Construct a new Triangle object with random color
   *
   * @param vertices Vertices of the triangle (in counter-clockwise order)
   */
  Triangle(const glm::mat3x3& vertices);

  /**
   * @brief Construct a new Triangle object
   *
   * @param list Vertices of the triangle (in counter-clockwise order)
   * @param color Color of the triangle
   */
  Triangle(std::initializer_list<glm::vec3> list, Color color);

  /**
   * @brief Construct a new Triangle object with random color
   *
   * @param list Vertices of the triangle (in counter-clockwise order)
   */
  Triangle(std::initializer_list<glm::vec3> list);

  /**
   * @brief Get the color of the triangle
   *
   * @return yar::Color
   */
  yar::Color get_color() const;

  /**
   * @brief Get the vertices of the triangle
   *
   * @return const glm::mat3x4&
   */
  const glm::mat3x4& get_vertices() const;

  /**
   * @brief Cycle the vertices ((A, B, C) -> (C, A, B))
   *
   */
  void cycle();

  /**
   * @brief Linearly interpolate a value between the values in the vertices
   *
   * @param p0 Value in the first vertex
   * @param p1 Value in the second vertex
   * @param p2 Value in the third vertex
   * @param point Point in which we want to know the value
   * @return float
   */
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

  /**
   * @brief Project the coordinates from 4-dimensional space to 3-dimensional
   * space
   *
   */
  void project_to_3d();

  /**
   * @brief Get the 2-dimensional bounding box of the triangle
   *
   * @return glm::vec4 (min x, max x, min y, max y)
   */
  glm::vec4 get_bounding_box() const;

  /**
   * @brief Check if the point is inside the 2-dimensional projection of the
   * triangle
   *
   * @param point
   * @return true if the point is inisde
   * @return false if the point is outside
   */
  bool is_inside(glm::vec2 point) const;

 private:
  glm::mat3x4 m_vertices;  // vertices of the triangle
  glm::mat3x3 m_vecs;
  yar::Color m_color;

  void update_vecs();
  glm::mat3x4 get_mat(std::initializer_list<glm::vec3> list);
};

}  // namespace yar
