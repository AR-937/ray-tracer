#ifndef SCENE_H
#define SCENE_H

#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <memory>
#include <vector>

namespace raytracer {

class Scene {
public:
  Scene() = default;

  // add objects to the scene
  void add_object(std::shared_ptr<hittable> object) {
    world.add(std::move(object));
  }

  // add a sphere to the scene
  void add_sphere(const point3 &center, double radius,
                  std::shared_ptr<material> mat) {
    add_object(std::make_shared<sphere>(center, radius, std::move(mat)));
  }

  // create materials
  std::shared_ptr<lambertian> create_lambertian(const color &albedo) {
    return std::make_shared<lambertian>(albedo);
  }

  std::shared_ptr<metal> create_metal(const color &albedo, double fuzz) {
    return std::make_shared<metal>(albedo, fuzz);
  }

  std::shared_ptr<dielectric> create_dielectric(double refraction_index) {
    return std::make_shared<dielectric>(refraction_index);
  }

  // create a simple scene
  void render_simple_scene();

  // recreate the original scene from "Ray Tracing in One Weekend"
  void render_weekend_scene();

  // get the world for rendering
  [[nodiscard]] const hittable_list &get_world() const { return world; }

private:
  hittable_list world;
};

} // namespace raytracer

#endif
