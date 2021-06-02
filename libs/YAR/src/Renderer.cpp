#include <stdlib.h>

#include <YAR/Renderer.hpp>
#include <YAR/Utils.hpp>
#include <algorithm>
#include <cmath>

namespace yar {

void Renderer::render(const World& world, const Camera& camera,
                      Screen* screen) {
  screen->clear();
  glm::mat4 view_mat = glm::inverse(camera.get_transform_matrix());
  glm::mat4 projection_mat = camera.get_projection_matrix();
  for (const Object& object : world.get_objects()) {
    draw_object(object, camera, view_mat, projection_mat, screen);
  }
}

void Renderer::draw_object(const Object& object, const Camera& camera,
                           const glm::mat4& view_mat,
                           const glm::mat4& projection_mat, Screen* screen) {
  glm::mat4 model_mat = object.get_transform_matrix();
  std::vector<Triangle> triangles;
  for (Triangle triangle : object.get_triangles()) {
    triangles.push_back(view_mat * model_mat * triangle);
  }
  triangles = clip(triangles, camera);
  for (Triangle triangle : triangles) {
    triangle = projection_mat * triangle;
    triangle.project_to_3d();
    draw_triangle(triangle, screen);
  }
}

void Renderer::draw_triangle(const Triangle& triangle, Screen* screen) {
  size_t m_width = screen->get_width();
  size_t m_height = screen->get_height();
  glm::vec4 box = triangle.get_bounding_box();
  int64_t minx = uv_to_screen(truncate(box[0], -1.f, 1.f), m_width);
  int64_t maxx = uv_to_screen(truncate(box[1], -1.f, 1.f), m_width);
  int64_t miny = uv_to_screen(truncate(box[2], -1.f, 1.f), m_height);
  int64_t maxy = uv_to_screen(truncate(box[3], -1.f, 1.f), m_height);

  assert(minx >= 0 && minx <= m_width);
  assert(maxx >= 0 && maxx <= m_width);
  assert(miny >= 0 && miny <= m_height);
  assert(maxy >= 0 && maxy <= m_height);

  Color color = triangle.get_color();
  glm::mat3x4 vertices = triangle.get_vertices();

  // iterate over all points inside the bounding box and draw them if they are
  // inside the triangle
  for (int64_t x = minx; x < maxx; ++x) {
    float xf = screen_to_uv(x, m_width);
    for (int64_t y = miny; y < maxy; ++y) {
      float yf = screen_to_uv(y, m_height);
      float z = triangle.interpolate(vertices[0].z, vertices[1].z,
                                     vertices[2].z, glm::vec2(xf, yf));
      glm::vec3 point(xf, yf, z);
      if (is_point_inside_frustum(point) && triangle.is_inside(point)) {
        screen->update_pixel(x, m_height - y - 1, point.z,
                             triangle.get_color());
      }
    }
  }
}

std::vector<Triangle> Renderer::clip(const std::vector<Triangle>& triangles,
                                     const Camera& camera) {
  std::vector<Triangle> ret;
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
        ret.push_back(Triangle(
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

        ret.push_back(Triangle(
            {vertices[0] + a * (vertices[1] - vertices[0]), vertices[1],
             vertices[0] + b * (vertices[2] - vertices[0])}));
        ret.push_back(Triangle({vertices[0] + b * (vertices[2] - vertices[0]),
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

bool Renderer::is_point_inside_frustum(const glm::vec3& point) const {
  return std::abs(point.x) <= 1 && std::abs(point.y) <= 1 &&
         std::abs(point.z) <= 1;
}

}  // namespace yar
