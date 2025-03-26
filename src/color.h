#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

namespace raytracer {

using color = vec3;

[[nodiscard]] constexpr double
linear_to_gamma(double linear_component) noexcept {
  if (linear_component > 0) {
    return std::sqrt(linear_component);
  }
  return 0;
}

inline void write_color(std::ostream &out, const color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // gamma correction
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  // translate the [0,1] component values to the byte range [0,255]
  static constexpr interval intensity(0.000, 0.999);
  int rbyte = static_cast<int>(256 * intensity.clamp(r));
  int gbyte = static_cast<int>(256 * intensity.clamp(g));
  int bbyte = static_cast<int>(256 * intensity.clamp(b));

  // write out the pixel color components
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

} // namespace raytracer

#endif
