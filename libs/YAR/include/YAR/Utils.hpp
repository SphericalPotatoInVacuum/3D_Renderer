#include <stdlib.h>

float truncate(float x, float min, float max) {
  if (x < min) {
    x = min;
  }
  if (x > max) {
    x = max;
  }
  return x;
}

float screen_to_uv(size_t x, size_t width) {
  return static_cast<float>(x) / width * 2 - 1.f;
}

size_t uv_to_screen(float uv, size_t width) {
  return (uv + 1.f) / 2.f * width;
}
