#include <stdlib.h>

#include <YAR/Renderer.hpp>
#include <algorithm>
#include <cmath>

float frand() {
  return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

void yar::Renderer::render(const yar::World& world, const yar::Camera& camera,
                           yar::Screen& screen) {
  screen.clear();
  glm::mat4 view = glm::inverse(camera.get_transform_matrix());
  glm::mat4 projection = camera.get_projection_matrix();

  for (const yar::Object& object : world.get_objects()) {
    glm::mat4 model = object.get_transform_matrix();
    std::vector<yar::Triangle> triangles;
    for (yar::Triangle triangle : object.get_triangles()) {
      triangles.push_back(view * model * triangle);
    }
    triangles = clip(triangles, camera);
    for (yar::Triangle triangle : triangles) {
      triangle = projection * triangle;
      triangle.project_to_3d();
      draw(triangle, screen);
    }
  }
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

void yar::Renderer::draw(const yar::Triangle& triangle, yar::Screen& screen) {
  size_t m_width = screen.get_width();
  size_t m_height = screen.get_height();
  glm::vec4 box = triangle.get_bounding_box();
  int64_t minx = (truncate(box[0], -1, 1) + 1) / 2 * m_width;
  int64_t maxx = (truncate(box[1], -1, 1) + 1) / 2 * m_width;
  int64_t miny = (truncate(box[2], -1, 1) + 1) / 2 * m_height;
  int64_t maxy = (truncate(box[3], -1, 1) + 1) / 2 * m_height;

  assert(minx >= 0 && minx <= m_width);
  assert(maxx >= 0 && maxx <= m_width);
  assert(miny >= 0 && miny <= m_height);
  assert(maxy >= 0 && maxy <= m_height);

  yar::Color color = triangle.get_color();
  glm::mat3x4 vertices = triangle.get_vertices();

  for (int64_t x = minx; x < maxx; ++x) {
    float xf = static_cast<float>(x) / m_width * 2 - 1;
    for (int64_t y = miny; y < maxy; ++y) {
      float yf = static_cast<float>(y) / m_height * 2 - 1;
      float z = triangle.interpolate(vertices[0].z, vertices[1].z,
                                     vertices[2].z, glm::vec2(xf, yf));
      yar::Color c =
          triangle.interpolate(yar::Color{255, 0, 0}, yar::Color{0, 255, 0},
                               yar::Color{0, 0, 255}, glm::vec2(xf, yf));
      glm::vec3 point(xf, yf, z);
      if (std::abs(point.x) <= 1 && std::abs(point.y) <= 1 &&
          triangle.is_inside(point)) {
        float zf = std::pow((z + 1) / 2.0, 16);
        color = yar::Color{255, 255, 255} * (1 - zf);
        screen.update_pixel(x, m_height - y - 1, point.z, color);
      }
    }
  }
}

std::vector<yar::Triangle> yar::Renderer::clip(
    const std::vector<yar::Triangle>& triangles, const yar::Camera& camera) {
  std::vector<yar::Triangle> ret;
  for (auto triangle : triangles) {
    std::vector<int> inside, outside;
    auto vertices = triangle.get_vertices();
    for (int i = 0; i < 3; ++i) {
      if (-vertices[i].z >= camera.get_near()) {
        inside.push_back(i);
      } else {
        outside.push_back(i);
      }
    }
    float a, b;
    switch (inside.size()) {
      case 0:
        // triangle is fully outside
        break;
      case 1:
        // 1 vertex is inside, clamp vertices to vertices of intersection
        if (inside[0] == 1) {
          triangle.cycle();
          triangle.cycle();
        } else if (inside[0] == 2) {
          triangle.cycle();
        }
        // now the zeroth vertex is inside
        vertices = triangle.get_vertices();
        a = (-camera.get_near() - vertices[0].z) /
            (vertices[1].z - vertices[0].z);
        b = (-camera.get_near() - vertices[0].z) /
            (vertices[2].z - vertices[0].z);
        ret.push_back(yar::Triangle(
            {vertices[0], vertices[0] + a * (vertices[1] - vertices[0]),
             vertices[0] + b * (vertices[2] - vertices[0])}));
        break;
      case 2:
        // 2 vertices are inside, construct 2 new triangles
        if (outside[0] == 1) {
          triangle.cycle();
          triangle.cycle();
        } else if (outside[0] == 2) {
          triangle.cycle();
        }
        // now the zeroth vertex is inside
        vertices = triangle.get_vertices();
        a = (-camera.get_near() - vertices[0].z) /
            (vertices[1].z - vertices[0].z);
        b = (-camera.get_near() - vertices[0].z) /
            (vertices[2].z - vertices[0].z);

        ret.push_back(yar::Triangle(
            {vertices[0] + a * (vertices[1] - vertices[0]), vertices[1],
             vertices[0] + b * (vertices[2] - vertices[0])}));
        ret.push_back(
            yar::Triangle({vertices[0] + b * (vertices[2] - vertices[0]),
                           vertices[1], vertices[2]}));
        break;
      case 3:
        ret.push_back(triangle);
        break;
      default:
        break;
    }
  }
  return ret;
}
