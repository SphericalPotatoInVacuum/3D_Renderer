#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <glm/vec3.hpp>
#include <memory>

namespace yar {

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

class Picture {
 private:
  size_t m_width;
  size_t m_height;
  std::shared_ptr<Color> m_data_ptr;

 public:
  Picture(){};
  Picture(size_t width, size_t height);

  void clear();
  yar::Color& operator()(size_t row, size_t col);

  const yar::Color* get_pixels() const;
};

}  // namespace yar
