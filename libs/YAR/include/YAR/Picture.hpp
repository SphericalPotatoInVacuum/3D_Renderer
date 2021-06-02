#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <YAR/Color.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

namespace yar {

class Picture {
 public:
  Picture(size_t width, size_t height);

  void clear();
  yar::Color& operator()(size_t x, size_t y);
  const yar::Color& operator()(size_t x, size_t y) const;

  const size_t get_width() const;
  const size_t get_height() const;

 private:
  size_t m_width;
  size_t m_height;
  std::vector<yar::Color> m_data;
};

}  // namespace yar
