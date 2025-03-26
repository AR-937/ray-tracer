#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>

namespace raytracer {

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;

// Constants
inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;

// Utility Functions
[[nodiscard]] constexpr double degrees_to_radians(double degrees) noexcept {
    return degrees * pi / 180.0;
}

// Thread-local random number generator for better performance and quality
inline std::mt19937& get_random_engine() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 generator(rd());
    return generator;
}

[[nodiscard]] inline double random_double() noexcept {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(get_random_engine());
}

[[nodiscard]] inline double random_double(double min, double max) noexcept {
    return min + (max - min) * random_double();
}

// Forward declarations
class ray;
class vec3;

} // namespace raytracer

#endif
