#pragma once
#include <stdint.h>

namespace yar {

using ColorType = uint8_t;

/**
 * @brief The Color class is used to make manipulations with the colors of the
 * pixels easier
 *
 */
class Color {
 public:
  /**
   * @brief Default constructor
   *
   */
  Color() = default;

  /**
   * @brief Construct a new Color object
   *
   * @param r_ Red component
   * @param g_ Green component
   * @param b_ Blue component
   */
  Color(ColorType r_, ColorType g_, ColorType b_);

  /**
   * @brief Multiply each component by the multiplier
   *
   * @param multiplier
   * @return Color&
   */
  Color& operator*=(float multiplier);

  friend Color operator*(const Color& color, float multiplier);

  friend Color operator*(float multiplier, const Color& color);

  Color& operator+=(const Color& color);

  friend Color operator+(const Color& color_a, const Color& color_b);

  ColorType r = 0;
  ColorType g = 0;
  ColorType b = 0;

  /**
   * @brief Frequently used colors
   *
   */
  static const Color Red;
  static const Color Green;
  static const Color Blue;
  static const Color Yellow;
  static const Color Cyan;
  static const Color Magenta;
  static const Color Black;
  static const Color White;
};

}  // namespace yar
