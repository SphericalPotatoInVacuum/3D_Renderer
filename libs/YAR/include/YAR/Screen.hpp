#pragma once

#include <YAR/Picture.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace yar {

/**
 * @brief Screen class to ease manipulation with the picture
 *
 */
class Screen {
 public:
  /**
   * @brief Construct a new Screen object
   *
   * @param width Width of the screen
   * @param height Height of the screen
   */
  Screen(size_t width, size_t height);

  /**
   * @brief Get the width of the screen
   *
   * @return size_t
   */
  size_t get_width() const;

  /**
   * @brief Get the height of the screen
   *
   * @return size_t
   */
  size_t get_height() const;

  /**
   * @brief Fill the screen with black and reset the z-buffer
   *
   */
  void clear();

  /**
   * @brief Get the picture object
   *
   * @return const yar::Picture&
   */
  const yar::Picture& get_picture() const;

  /**
   * @brief Update the pixel at coordinates (x, y) with color c depending on the
   * z coordinate
   *
   * @param x
   * @param y
   * @param z
   * @param c
   */
  void update_pixel(size_t x, size_t y, float z, Color c);

 private:
  yar::Picture m_picture;
  std::vector<float> m_zbuf;
  static constexpr const float k_maximal_z_value = 1.f;
};
}  // namespace yar
