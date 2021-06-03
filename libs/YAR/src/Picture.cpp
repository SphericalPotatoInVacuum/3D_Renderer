#include <string.h>

#include <YAR/Picture.hpp>
#include <random>

namespace yar {

Picture::Picture(size_t width, size_t height)
    : m_width(width), m_height(height) {
  assert(("Width and height must be greater than zero",
          width >= 0 && height >= 0));
  m_data = std::vector<Color>(width * height, {0, 0, 0});
}

void Picture::clear() {
  m_data.assign(m_data.size(), {0, 0, 0});
}

Color& Picture::operator()(size_t x, size_t y) {
  return m_data[y * m_width + x];
}

const Color& Picture::operator()(size_t x, size_t y) const {
  return m_data[y * m_width + x];
}

const size_t Picture::get_width() const {
  return m_width;
}

const size_t Picture::get_height() const {
  return m_height;
}

}  // namespace yar
