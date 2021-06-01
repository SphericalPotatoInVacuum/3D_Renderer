#pragma once

#include <YAR/Camera.hpp>
#include <YAR/Picture.hpp>
#include <YAR/Screen.hpp>
#include <YAR/World.hpp>

namespace yar {
class Renderer {
 private:
  void draw(const Triangle& triangle, yar::Screen& screen);
  std::vector<yar::Triangle> clip(const std::vector<yar::Triangle>& triangles,
                                  const yar::Camera& camera);

 public:
  void render(const yar::World& world, const yar::Camera& camera,
              yar::Screen& screen);
};
}  // namespace yar
