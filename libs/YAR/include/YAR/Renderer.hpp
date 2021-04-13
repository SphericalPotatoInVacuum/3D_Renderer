#pragma once

#include <YAR/Camera.hpp>
#include <YAR/Picture.hpp>
#include <YAR/Screen.hpp>
#include <YAR/World.hpp>

namespace yar {
class Renderer {
 public:
  Renderer();
  Renderer(size_t width, size_t height);

  const Picture& render();

 private:
  void draw(const Triangle& triangle);

  yar::World m_world;
  yar::Camera m_camera;
  yar::Screen m_screen;

  size_t m_width;
  size_t m_height;
};
}  // namespace yar
