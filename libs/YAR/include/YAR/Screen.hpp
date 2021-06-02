#pragma once

#include <YAR/Picture.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace yar {
class Screen {
 public:
  Screen(size_t width, size_t height);

  size_t get_width() const;
  size_t get_height() const;

  void clear();
  const yar::Picture& get_picture() const;

  void update_pixel(size_t x, size_t y, float z, Color c);

 private:
  yar::Picture m_picture;
  std::vector<float> m_zbuf;
  static constexpr const float k_maximal_z_value = 1.f;
};
}  // namespace yar
