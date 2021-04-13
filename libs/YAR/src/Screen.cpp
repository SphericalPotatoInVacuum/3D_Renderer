#include <YAR/Screen.hpp>

yar::Screen::Screen(size_t width, size_t height) : m_picture(width, height) {}

size_t yar::Screen::get_width() const {
  return m_width;
}

size_t yar::Screen::get_height() const {
  return m_height;
}

const yar::Picture& yar::Screen::get_picture() const {
  return m_picture;
}

void yar::Screen::set_pixel(size_t x, size_t y, Color c) {
  m_picture(y, x) = c;
}
