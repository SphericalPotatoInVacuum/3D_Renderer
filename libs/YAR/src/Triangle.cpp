#include <YAR/Triangle.hpp>
#include <algorithm>
#include <glm/gtx/normal.hpp>
#include <stdexcept>

float edge_function(glm::vec2 vec, glm::vec2 point) {
  return point.x * vec.y - point.y * vec.x;
}

yar::Triangle::Triangle(const glm::mat3x3 &vertices, Color color)
    : m_color(color) {
  m_vertices = glm::mat3x4(vertices);
  for (int i = 0; i < 3; ++i) {
    m_vertices[i].w = 1;
  }
  update();
}

yar::Triangle::Triangle(std::initializer_list<glm::vec3> list, yar::Color color)
    : Triangle(get_mat(list), color) {}

yar::Triangle::Triangle(const glm::mat3x3 &vertices)
    : Triangle(vertices,
               yar::Color{(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()}) {}

yar::Triangle::Triangle(std::initializer_list<glm::vec3> list)
    : Triangle(list,
               yar::Color{(uint8_t)rand(), (uint8_t)rand(), (uint8_t)rand()}) {}

yar::Color yar::Triangle::get_color() const {
  return m_color;
}

glm::vec4 yar::Triangle::get_bounding_box() const {
  glm::vec4 box = {1, -1, 1, -1};
  for (size_t i = 0; i < 3; ++i) {
    box[0] = std::min(box[0], m_vertices[i].x);
    box[1] = std::max(box[1], m_vertices[i].x);
    box[2] = std::min(box[2], m_vertices[i].y);
    box[3] = std::max(box[3], m_vertices[i].y);
  }
  return box;
}

glm::mat3x4 yar::Triangle::get_vertices() const {
  return m_vertices;
}

bool yar::Triangle::is_inside(glm::vec2 point) const {
  for (size_t i = 0; i < 3; ++i) {
    glm::vec2 p = point - glm::vec2(m_vertices[i]);
    if (edge_function(m_vecs[i], p) > 0) {
      return false;
    }
  }
  return true;
}

void yar::Triangle::cycle() {
  std::swap(m_vertices[0], m_vertices[2]);
  std::swap(m_vertices[1], m_vertices[2]);
  std::swap(m_vecs[0], m_vecs[2]);
  std::swap(m_vecs[1], m_vecs[2]);
}

yar::Triangle yar::Triangle::operator*(const glm::mat4 &mat) const {
  yar::Triangle tri(*this);
  for (size_t i = 0; i < 3; ++i) {
    tri.m_vertices[i] = mat * m_vertices[i];
  }
  tri.update();
  return tri;
}

yar::Triangle yar::operator*(const glm::mat4 &mat, const yar::Triangle tri) {
  return tri * mat;
}

void yar::Triangle::project_to_3d() {
  for (int i = 0; i < 3; ++i) {
    m_vertices[i] /= m_vertices[i].w;
  }

  update();
}

void yar::Triangle::update() {
  for (int i = 0; i < 3; ++i) {
    m_vecs[i] = glm::vec3(m_vertices[(i + 1) % 3] - m_vertices[i]);
  }
}

glm::mat3x4 yar::Triangle::get_mat(std::initializer_list<glm::vec3> list) {
  assert(("List must have 3 elements", list.size() == 3));
  glm::mat3x3 mat;
  int i = 0;
  for (const auto &vec : list) {
    mat[i] = vec;
    ++i;
  }
  return mat;
}
