#pragma once

#include <YAR/Picture.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace yar {
class Screen {
 private:
  yar::Picture m_picture;
  std::vector<float> m_zbuf;
  size_t m_width = 0;
  size_t m_height = 0;

 public:
  Screen() {}
  Screen(size_t width, size_t height);

  size_t get_width() const;
  size_t get_height() const;

  void clear();
  const yar::Picture& get_picture() const;

  void update_pixel(size_t x, size_t y, float z, Color c);
};
}  // namespace yar
