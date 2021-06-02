#include <YAR/Screen.hpp>

namespace yar {

Screen::Screen(size_t width, size_t height) : m_picture(width, height) {
  assert(("Width and height must be greater than zero",
          width >= 0 && height >= 0));

  m_zbuf = std::vector<float>(width * height, k_maximal_z_value);
}

size_t Screen::get_width() const {
  return m_picture.get_width();
}

size_t Screen::get_height() const {
  return m_picture.get_height();
}

void Screen::clear() {
  m_picture.clear();
  m_zbuf.assign(m_picture.get_width() * m_picture.get_height(),
                k_maximal_z_value);
}

const Picture& Screen::get_picture() const {
  return m_picture;
}

void Screen::update_pixel(size_t x, size_t y, float z, Color c) {
  assert(("x must be in range [0, screen width)",
          0 <= x && x < m_picture.get_width()));
  assert(("y must be in range [0, screen height)",
          0 <= y && y < m_picture.get_height()));
  if (z < m_zbuf[x * m_picture.get_width() + y]) {
    m_zbuf[x * m_picture.get_height() + y] = z;
    m_picture(x, y) = c;
  }
}

}  // namespace yar
