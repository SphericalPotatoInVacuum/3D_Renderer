#include <YAR/Triangle.hpp>
#include <algorithm>
#include <stdexcept>

yar::Triangle::Triangle(std::array<glm::vec4, 3> points)
    : m_points(points), m_color{rand(), rand(), rand()} {
  m_vecs[0] = glm::vec2(m_points[1] - m_points[0]);
  m_vecs[1] = glm::vec2(m_points[2] - m_points[1]);
  m_vecs[2] = glm::vec2(m_points[0] - m_points[2]);
}

yar::Triangle::Triangle(std::initializer_list<glm::vec4> list) {
  if (list.size() != 3) {
    throw std::invalid_argument("List must have 3 elements");
  }
  std::array<glm::vec4, 3> points;
  auto it = points.begin();
  for (const glm::vec4 &point : list) {
    *it = point;
    ++it;
  }
  *this = yar::Triangle(points);
}

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

bool yar::Triangle::is_inside(glm::vec2 point) const {
  for (size_t i = 0; i < 3; ++i) {
    glm::vec2 p = point - glm::vec2(m_points[i]);
    if (p.x * m_vecs[i].y - m_vecs[i].x * p.y < 0) {
      return false;
    }
  }
  return true;
}
