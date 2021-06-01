#include <YAR/Triangle.hpp>
#include <algorithm>
#include <glm/gtx/normal.hpp>
#include <stdexcept>

float edge_function(glm::vec2 vec, glm::vec2 point) {
  return point.x * vec.y - point.y * vec.x;
}

yar::Triangle::Triangle(std::array<glm::vec3, 3> points, Color color)
    : m_color(color) {
  for (int i = 0; i < 3; ++i) {
    m_points[i] = glm::vec4(points[i], 1);
  }
  update();
}

yar::Triangle::Triangle(std::initializer_list<glm::vec3> list,
                        yar::Color color) {
  if (list.size() != 3) {
    throw std::invalid_argument("List must have 3 elements");
  }
  std::array<glm::vec3, 3> points;
  auto it = points.begin();
  for (const glm::vec3 &point : list) {
    *it = point;
    ++it;
  }
  *this = yar::Triangle(points, color);
}

yar::Triangle::Triangle(std::array<glm::vec3, 3> points)
    : Triangle(points,
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
    box[0] = std::min(box[0], m_points[i].x);
    box[1] = std::max(box[1], m_points[i].x);
    box[2] = std::min(box[2], m_points[i].y);
    box[3] = std::max(box[3], m_points[i].y);
  }
  return box;
}

std::array<glm::vec4, 3> yar::Triangle::get_points() const {
  return m_points;
}

bool yar::Triangle::is_inside(glm::vec2 point) const {
  for (size_t i = 0; i < 3; ++i) {
    glm::vec2 p = point - glm::vec2(m_points[i]);
    if (edge_function(m_vecs[i], p) > 0) {
      return false;
    }
  }
  return true;
}

void yar::Triangle::cycle() {
  std::swap(m_points[0], m_points[2]);
  std::swap(m_points[1], m_points[2]);
  std::swap(m_vecs[0], m_vecs[2]);
  std::swap(m_vecs[1], m_vecs[2]);
}

yar::Triangle yar::Triangle::operator*(const glm::mat4 &mat) const {
  yar::Triangle tri(*this);
  for (size_t i = 0; i < 3; ++i) {
    tri.m_points[i] = mat * m_points[i];
  }
  tri.update();
  return tri;
}

yar::Triangle yar::operator*(const glm::mat4 &mat, const yar::Triangle tri) {
  return tri * mat;
}

void yar::Triangle::normalize() {
  for (auto &point : m_points) {
    point /= point.w;
  }

  update();
}

void yar::Triangle::update() {
  for (int i = 0; i < 3; ++i) {
    m_vecs[i] = glm::vec3(m_points[(i + 1) % 3] - m_points[i]);
  }
}
