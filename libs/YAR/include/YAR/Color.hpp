#pragma once
#include <stdint.h>

namespace yar {

using ColorType = uint8_t;

class Color {
 public:
  Color() = default;
  Color(ColorType r_, ColorType g_, ColorType b_);

  Color& operator*=(float multiplier);

  friend Color operator*(const Color& color, float multiplier);

  friend Color operator*(float multiplier, const Color& color);

  Color& operator+=(const Color& color);

  friend Color operator+(const Color& color_a, const Color& color_b);

  ColorType r = 0;
  ColorType g = 0;
  ColorType b = 0;

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
