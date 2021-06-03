#pragma once

#include <YAR/Camera.hpp>
#include <YAR/Picture.hpp>
#include <YAR/Screen.hpp>
#include <YAR/World.hpp>

namespace yar {

/**
 * @brief Main class responsible for rendering the scene
 */
class Renderer {
 public:
  /*!
   * @brief Renders the scene to the screen object
   * @param world Holds the objects that will be rendered
   * @param camera The rendering will be done from the camera's point of view
   * @param screen The resulting image will be written to this screen
   */
  void render(const yar::World& world, const yar::Camera& camera,
              yar::Screen* screen);

 private:
  void draw_object(const Object& object, const yar::Camera& camera,
                   const glm::mat4& view_mat, const glm::mat4& projection_mat,
                   yar::Screen* screen);
  void draw_triangle(const Triangle& triangle, yar::Screen* screen);

  std::vector<yar::Triangle> clip(const std::vector<yar::Triangle>& triangles,
                                  const yar::Camera& camera);

  bool is_point_inside_frustum(const glm::vec3& point) const;
};

}  // namespace yar
