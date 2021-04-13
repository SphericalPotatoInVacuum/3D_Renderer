#include <stdlib.h>

#include <YAR/Renderer.hpp>
#include <algorithm>

float frand() {
  return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

yar::Renderer::Renderer(size_t width, size_t height)
    : m_screen(width, height), m_width(width), m_height(height) {
  float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
  m_camera = Camera(glm::vec4(0), glm::vec4(0), glm::radians(70.0f), 1.0f,
                    100.0f, aspect_ratio, yar::ProjectionType::PERSPECTIVE);
  std::vector<yar::Triangle> triangles = {
      {{-1, 1, -1, 1}, {1, 1, -1, 1}, {0, 0, -1, 1}},
      {{1, 1, -1, 1}, {1, 1, 1, 1}, {1, 0, 0, 1}}};
  m_world.add_object(yar::Object({0, 0, 0}, {0, 0, 0}, triangles));
}

const yar::Picture& yar::Renderer::render() {
  const std::vector<yar::Triangle>& triangles = m_world.get_triangles();
  for (const yar::Triangle& triangle : triangles) {
    draw(triangle);
  }

  return m_screen.get_picture();
}

void yar::Renderer::draw(const yar::Triangle& triangle) {
  glm::vec4 box = triangle.get_bounding_box();
  size_t minx = (box[0] + 1) / 2 * m_width;
  size_t maxx = (box[1] + 1) / 2 * m_width;
  size_t miny = (box[2] + 1) / 2 * m_height;
  size_t maxy = (box[3] + 1) / 2 * m_height;

  yar::Color color = triangle.get_color();

  for (size_t x = minx; x <= maxx; ++x) {
    for (size_t y = miny; y <= maxy; ++y) {
      float xf = static_cast<float>(x);
      float yf = static_cast<float>(y);
      glm::vec2 point(xf / m_width * 2 - 1, yf / m_height * 2 - 1);
      if (triangle.is_inside(point)) {
        m_screen.set_pixel(x, m_height - y, color);
      }
    }
  }
}
