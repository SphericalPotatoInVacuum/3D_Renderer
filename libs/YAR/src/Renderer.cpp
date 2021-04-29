#include <stdlib.h>

#include <YAR/Renderer.hpp>
#include <algorithm>
#include <cmath>

float frand() {
  return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

yar::Renderer::Renderer(yar::World& world, yar::Camera& camera, size_t width,
                        size_t height)
    : m_world(world),
      m_camera(camera),
      m_screen(width, height),
      m_width(width),
      m_height(height) {}

const yar::Picture& yar::Renderer::render() {
  m_screen.clear();
  glm::mat4 view = glm::inverse(m_camera.get_transform_matrix());
  glm::mat4 projection = m_camera.get_projection_matrix();
  glm::mat4 mvp;
  for (yar::Object* object_ptr : m_world.get_objects()) {
    glm::mat4 model = object_ptr->get_transform_matrix();
    mvp = projection * view * model;
    for (yar::Triangle triangle : object_ptr->get_triangles()) {
      triangle = triangle * mvp;
      triangle.normalize();
      draw(triangle);
    }
  }

  return m_screen.get_picture();
}

float truncate(float x, float min, float max) {
  if (x < min) {
    x = min;
  }
  if (x > max) {
    x = max;
  }
  return x;
}

void yar::Renderer::draw(const yar::Triangle& triangle) {
  glm::vec4 box = triangle.get_bounding_box();
  int64_t minx = (truncate(box[0], -1, 1) + 1) / 2 * m_width + 1;
  int64_t maxx = (truncate(box[1], -1, 1) + 1) / 2 * m_width - 1;
  int64_t miny = (truncate(box[2], -1, 1) + 1) / 2 * m_height + 1;
  int64_t maxy = (truncate(box[3], -1, 1) + 1) / 2 * m_height - 1;

  assert(minx >= 0 && minx <= m_width);
  assert(maxx >= 0 && maxx <= m_width);
  assert(miny >= 0 && miny <= m_height);
  assert(maxy >= 0 && maxy <= m_height);

  yar::Color color = triangle.get_color();

  for (int64_t x = minx; x < maxx; ++x) {
    float xf = static_cast<float>(x) / m_width * 2 - 1;
    std::array<float, 2> ys = triangle.get_y(xf);
    miny = (ys[0] + 1) / 2 * m_width;
    maxy = (ys[1] + 1) / 2 * m_width;
    for (int64_t y = miny; y < maxy; ++y) {
      float yf = static_cast<float>(y) / m_height * 2 - 1;
      glm::vec3 point(xf, yf, triangle.get_z(xf, yf));
      if (std::abs(point.x) <= 1 && std::abs(point.y) <= 1 &&
          triangle.is_inside(point)) {
        m_screen.update_pixel(x, m_height - y - 1, point.z, color);
      }
    }
  }
}
