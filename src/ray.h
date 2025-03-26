#ifndef RAY_H
#define RAY_H

#include "vec3.h"

namespace raytracer {

class ray {
public:
  constexpr ray() noexcept = default;

  constexpr ray(const point3 &origin, const vec3 &direction) noexcept
      : orig(origin), dir(direction) {}

  constexpr ray(const ray &) noexcept = default;
  constexpr ray(ray &&) noexcept = default;
  constexpr ray &operator=(const ray &) noexcept = default;
  constexpr ray &operator=(ray &&) noexcept = default;

  [[nodiscard]] constexpr const point3 &origin() const noexcept { return orig; }
  [[nodiscard]] constexpr const vec3 &direction() const noexcept { return dir; }

  [[nodiscard]] constexpr point3 at(double t) const noexcept {
    return orig + t * dir;
  }

private:
  point3 orig{0, 0, 0};
  vec3 dir{0, 0, 0};
};

} // namespace raytracer
#endif
