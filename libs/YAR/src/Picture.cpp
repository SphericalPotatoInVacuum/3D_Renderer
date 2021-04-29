#include <string.h>

#include <YAR/Picture.hpp>
#include <random>

yar::Picture::Picture(size_t width, size_t height)
    : m_width(width),
      m_height(height),
      m_data_ptr((yar::Color*)malloc(width * height * sizeof(yar::Color)),
                 free) {
  for (size_t i = 0; i < width * height; ++i) {
    m_data_ptr.get()[i] = {0, 0, 0};
  }
}

void yar::Picture::clear() {
  memset(m_data_ptr.get(), 0, m_width * m_height * sizeof(yar::Color));
}

yar::Color& yar::Picture::operator()(size_t x, size_t y) {
  return m_data_ptr.get()[y * m_width + x];
}

const yar::Color* yar::Picture::get_pixels() const {
  return m_data_ptr.get();
}
