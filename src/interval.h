#ifndef INTERVAL_H
#define INTERVAL_H

#include "utilities.h"

namespace raytracer {

class interval {
public:
  double min, max;

  // Default interval is empty
  constexpr interval() noexcept : min(+infinity), max(-infinity) {}

  constexpr interval(double min, double max) noexcept : min(min), max(max) {}

  // Copy and move operations
  constexpr interval(const interval&) noexcept = default;
  constexpr interval(interval&&) noexcept = default;
  constexpr interval& operator=(const interval&) noexcept = default;
  constexpr interval& operator=(interval&&) noexcept = default;

  [[nodiscard]] constexpr double size() const noexcept { return max - min; }

  [[nodiscard]] constexpr bool contains(double x) const noexcept { return min <= x && x <= max; }

  [[nodiscard]] constexpr bool surrounds(double x) const noexcept { return min < x && x < max; }

  [[nodiscard]] constexpr double clamp(double x) const noexcept {
    if (x < min)
      return min;
    if (x > max)
      return max;
    return x;
  }
};

// Define constants outside the class
inline const interval empty(+infinity, -infinity);
inline const interval universe(-infinity, +infinity);

} // namespace raytracer

#endif
