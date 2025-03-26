#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utilities.h"
#include "vec3.h"

namespace raytracer {

class material {
public:
    material() noexcept = default;
    virtual ~material() = default;

    // Prevent slicing
    material(const material&) = default;
    material& operator=(const material&) = default;
    material(material&&) noexcept = default;
    material& operator=(material&&) noexcept = default;

    virtual bool scatter([[maybe_unused]] const ray& r_in, 
                      [[maybe_unused]] const hit_record& rec,
                      [[maybe_unused]] color& attenuation, 
                      [[maybe_unused]] ray& scattered) const {
        return false;
    }
};

class lambertian : public material {
public:
    explicit lambertian(const color& albedo) noexcept : albedo(albedo) {}

    bool scatter([[maybe_unused]] const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override;

private:
    color albedo;
};

class metal : public material {
public:
    metal(const color& albedo, double fuzz) noexcept
        : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override;

private:
    color albedo;
    double fuzz;
};

class dielectric : public material {
public:
    explicit dielectric(double refraction_index) noexcept : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override;

private:
    // Refractive index in vacuum or air
    double refraction_index;

    [[nodiscard]] static double reflectance(double cosine, double refraction_index) noexcept;
};

} // namespace raytracer

#endif
