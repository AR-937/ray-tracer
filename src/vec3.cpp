#include "vec3.h"

namespace raytracer {

[[nodiscard]] vec3 random_in_unit_disk() noexcept {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

[[nodiscard]] vec3 random_unit_vector() noexcept {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / std::sqrt(lensq);
    }
}

[[nodiscard]] vec3 random_on_hemisphere(const vec3& normal) noexcept {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

[[nodiscard]] vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) noexcept {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel =
        -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

} // namespace raytracer 