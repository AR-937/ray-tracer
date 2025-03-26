#ifndef VEC3_H
#define VEC3_H

#include "utilities.h"
#include <array>
#include <cmath>
#include <iostream>

namespace raytracer {

class vec3 {
public:
  std::array<double, 3> e{0, 0, 0};

  constexpr vec3() noexcept = default;
  constexpr vec3(double e0, double e1, double e2) noexcept : e{e0, e1, e2} {}

  constexpr vec3(const vec3 &) noexcept = default;
  constexpr vec3(vec3 &&) noexcept = default;
  constexpr vec3 &operator=(const vec3 &) noexcept = default;
  constexpr vec3 &operator=(vec3 &&) noexcept = default;

  [[nodiscard]] constexpr double x() const noexcept { return e[0]; }
  [[nodiscard]] constexpr double y() const noexcept { return e[1]; }
  [[nodiscard]] constexpr double z() const noexcept { return e[2]; }

  [[nodiscard]] constexpr vec3 operator-() const noexcept {
    return vec3(-e[0], -e[1], -e[2]);
  }
  [[nodiscard]] constexpr double operator[](int i) const noexcept {
    return e[i];
  }
  [[nodiscard]] constexpr double &operator[](int i) noexcept { return e[i]; }

  constexpr vec3 &operator+=(const vec3 &v) noexcept {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  constexpr vec3 &operator*=(double t) noexcept {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  constexpr vec3 &operator/=(double t) noexcept { return *this *= 1.0 / t; }

  [[nodiscard]] double length() const noexcept {
    return std::sqrt(length_squared());
  }

  [[nodiscard]] constexpr double length_squared() const noexcept {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  [[nodiscard]] constexpr bool near_zero() const noexcept {
    // return true if vector is close to zero in all dimensions
    constexpr auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }

  static vec3 random() noexcept;
  static vec3 random(double min, double max) noexcept;
};

// point3 alias vec3
using point3 = vec3;

// vector Utility Functions - Declarations
[[nodiscard]] inline std::ostream &operator<<(std::ostream &out, const vec3 &v);
[[nodiscard]] constexpr vec3 operator+(const vec3 &u, const vec3 &v) noexcept;
[[nodiscard]] constexpr vec3 operator-(const vec3 &u, const vec3 &v) noexcept;
[[nodiscard]] constexpr vec3 operator*(const vec3 &u, const vec3 &v) noexcept;
[[nodiscard]] constexpr vec3 operator*(double t, const vec3 &v) noexcept;
[[nodiscard]] constexpr vec3 operator*(const vec3 &v, double t) noexcept;
[[nodiscard]] constexpr vec3 operator/(const vec3 &v, double t) noexcept;
[[nodiscard]] constexpr double dot(const vec3 &u, const vec3 &v) noexcept;
[[nodiscard]] constexpr vec3 cross(const vec3 &u, const vec3 &v) noexcept;
[[nodiscard]] vec3 unit_vector(const vec3 &v) noexcept;
[[nodiscard]] vec3 random_in_unit_disk() noexcept;
[[nodiscard]] vec3 random_unit_vector() noexcept;
[[nodiscard]] vec3 random_on_hemisphere(const vec3 &normal) noexcept;
[[nodiscard]] constexpr vec3 reflect(const vec3 &v, const vec3 &n) noexcept;
[[nodiscard]] vec3 refract(const vec3 &uv, const vec3 &n,
                           double etai_over_etat) noexcept;

// inline implementations of simple vector ops
inline vec3 vec3::random() noexcept {
  return vec3(random_double(), random_double(), random_double());
}

inline vec3 vec3::random(double min, double max) noexcept {
  return vec3(random_double(min, max), random_double(min, max),
              random_double(min, max));
}

[[nodiscard]] inline std::ostream &operator<<(std::ostream &out,
                                              const vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

[[nodiscard]] constexpr vec3 operator+(const vec3 &u, const vec3 &v) noexcept {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

[[nodiscard]] constexpr vec3 operator-(const vec3 &u, const vec3 &v) noexcept {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

[[nodiscard]] constexpr vec3 operator*(const vec3 &u, const vec3 &v) noexcept {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

[[nodiscard]] constexpr vec3 operator*(double t, const vec3 &v) noexcept {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

[[nodiscard]] constexpr vec3 operator*(const vec3 &v, double t) noexcept {
  return t * v;
}

[[nodiscard]] constexpr vec3 operator/(const vec3 &v, double t) noexcept {
  return (1.0 / t) * v;
}

[[nodiscard]] constexpr double dot(const vec3 &u, const vec3 &v) noexcept {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

[[nodiscard]] constexpr vec3 cross(const vec3 &u, const vec3 &v) noexcept {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

[[nodiscard]] inline vec3 unit_vector(const vec3 &v) noexcept {
  return v / v.length();
}

[[nodiscard]] constexpr vec3 reflect(const vec3 &v, const vec3 &n) noexcept {
  return v - 2 * dot(v, n) * n;
}

} // namespace raytracer

#endif
