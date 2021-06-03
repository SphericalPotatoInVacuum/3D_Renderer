#include <YAR/Triangle.hpp>
#include <algorithm>
#include <glm/gtx/normal.hpp>
#include <stdexcept>

namespace yar {

float get_signed_cp_length(glm::vec2 vec, glm::vec2 point) {
  return point.x * vec.y - point.y * vec.x;
}

Triangle::Triangle(const glm::mat3x3 &vertices, Color color) : m_color(color) {
  m_vertices = glm::mat3x4(vertices);
  for (int i = 0; i < 3; ++i) {
    m_vertices[i].w = 1;
  }
  update_vecs();
}
Triangle::Triangle(const glm::mat3x3 &vertices)
    : Triangle(vertices,
               Color{(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()}) {}

Triangle::Triangle(std::initializer_list<glm::vec3> list, Color color)
    : Triangle(get_mat(list), color) {}

Triangle::Triangle(std::initializer_list<glm::vec3> list)
    : Triangle(get_mat(list)) {}

Color Triangle::get_color() const {
  return m_color;
}

const glm::mat3x4 &Triangle::get_vertices() const {
  return m_vertices;
}

void Triangle::cycle() {
  std::swap(m_vertices[0], m_vertices[2]);
  std::swap(m_vertices[1], m_vertices[2]);
  std::swap(m_vecs[0], m_vecs[2]);
  std::swap(m_vecs[1], m_vecs[2]);
}

Triangle &Triangle::operator*=(const glm::mat4 &mat) {
  m_vertices = mat * m_vertices;
  update_vecs();
  return *this;
}

Triangle operator*(const glm::mat4 &mat, const Triangle &tri) {
  Triangle result = tri;
  result *= mat;
  result.update_vecs();
  return result;
}

void Triangle::project_to_3d() {
  for (int i = 0; i < 3; ++i) {
    m_vertices[i] /= m_vertices[i].w;
  }

  update_vecs();
}

glm::vec4 Triangle::get_bounding_box() const {
  glm::vec4 box = {1, -1, 1, -1};
  for (size_t i = 0; i < 3; ++i) {
    box[0] = std::min(box[0], m_vertices[i].x);
    box[1] = std::max(box[1], m_vertices[i].x);
    box[2] = std::min(box[2], m_vertices[i].y);
    box[3] = std::max(box[3], m_vertices[i].y);
  }
  return box;
}

bool Triangle::is_inside(glm::vec2 point) const {
  // point is inside if it lies to the left of each edge
  // (the 3rd coordinate of the cross product of AP and AB is negative for
  // point P and edge AB)
  for (size_t i = 0; i < 3; ++i) {
    glm::vec2 p = point - glm::vec2(m_vertices[i]);
    if (get_signed_cp_length(m_vecs[i], p) > 0) {
      return false;
    }
  }
  return true;
}

void Triangle::update_vecs() {
  for (int i = 0; i < 3; ++i) {
    m_vecs[i] = glm::vec3(m_vertices[(i + 1) % 3] - m_vertices[i]);
  }
}

glm::mat3x4 Triangle::get_mat(std::initializer_list<glm::vec3> list) {
  assert(("List must have 3 elements", list.size() == 3));
  glm::mat3x3 mat;
  int i = 0;
  for (const auto &vec : list) {
    mat[i] = vec;
    ++i;
  }
  return mat;
}

}  // namespace yar
