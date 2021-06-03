#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <YAR/Color.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

namespace yar {

/**
 * @brief Utility class to ease the manipulation with the pixels
 *
 */
class Picture {
 public:
  /**
   * @brief Construct a new Picture object
   *
   * @param width Width of the picture
   * @param height Height of the picture
   */
  Picture(size_t width, size_t height);

  /**
   * @brief Clear the picture (fill black)
   *
   */
  void clear();

  /**
   * @brief Get access to the pixel with coordinates (x, y)
   *
   * @param x
   * @param y
   * @return yar::Color&
   */
  yar::Color& operator()(size_t x, size_t y);

  /**
   * @brief Get access to the pixel with coordinates (x, y)
   *
   * @param x
   * @param y
   * @return yar::Color&
   */
  const yar::Color& operator()(size_t x, size_t y) const;

  /**
   * @brief Get the width of the picture
   *
   * @return const size_t
   */
  const size_t get_width() const;

  /**
   * @brief Get the height of the picture
   *
   * @return const size_t
   */
  const size_t get_height() const;

 private:
  size_t m_width;
  size_t m_height;
  std::vector<yar::Color> m_data;
};

}  // namespace yar
