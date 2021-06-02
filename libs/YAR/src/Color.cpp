#include <YAR/Color.hpp>

namespace yar {

using ColorType = uint8_t;

Color::Color(ColorType r_, ColorType g_, ColorType b_) : r(r_), g(g_), b(b_) {}

Color& Color::operator*=(float multiplier) {
  r *= multiplier;
  g *= multiplier;
  b *= multiplier;
  return *this;
}

Color operator*(const Color& color, float multiplier) {
  Color result = color;
  result *= multiplier;
  return result;
}

Color operator*(float multiplier, const Color& color) {
  return color * multiplier;
}

Color& Color::operator+=(const Color& color) {
  r += color.r;
  g += color.g;
  b += color.b;
  return *this;
}

Color operator+(const Color& color_a, const Color& color_b) {
  Color result = color_a;
  result += color_b;
  return result;
}

const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Cyan(0, 255, 255);
const Color Color::Magenta(255, 0, 255);
const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);

}  // namespace yar
