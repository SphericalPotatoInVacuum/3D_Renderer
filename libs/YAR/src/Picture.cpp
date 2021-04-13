#include <YAR/Picture.hpp>
#include <random>

yar::Picture::Picture(size_t width, size_t height)
    : m_width(width),
      m_height(height),
      m_data_ptr(std::make_unique<Color[]>(width * height)) {
  for (size_t i = 0; i < width * height; ++i) {
    m_data_ptr[i] = {rand() % 255, rand() % 255, rand() % 255};
  }
}

yar::Color& yar::Picture::operator()(size_t row, size_t col) {
  return m_data_ptr[row * m_width + col];
}

const yar::Color* yar::Picture::get_pixels() const {
  return m_data_ptr.get();
}
