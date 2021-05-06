#include <YAR/Screen.hpp>

yar::Screen::Screen(size_t width, size_t height)
    : m_picture(width, height),
      m_width(width),
      m_height(height),
      m_zbuf(width * height, -1) {}

size_t yar::Screen::get_width() const {
  return m_width;
}

size_t yar::Screen::get_height() const {
  return m_height;
}

const yar::Picture& yar::Screen::get_picture() const {
  return m_picture;
}

void yar::Screen::update_pixel(size_t x, size_t y, float z, Color c) {
  if (z < m_zbuf[x * m_width + y]) {
    m_zbuf[x * m_width + y] = z;
    m_picture(x, y) = c;
  }
}

void yar::Screen::clear() {
  m_picture.clear();
  m_zbuf.assign(m_width * m_height, 1);
}
