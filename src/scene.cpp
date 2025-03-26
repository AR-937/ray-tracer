#include "scene.h"
#include "utilities.h"

namespace raytracer {

void Scene::render_simple_scene() {
  // Ground - a large green sphere
  auto ground_material = create_lambertian(color(0.2, 0.8, 0.2));
  add_sphere(point3(0, -1000, 0), 1000, ground_material);

  // Center - glass sphere
  auto glass_material = create_dielectric(1.5);
  add_sphere(point3(0, 1, 0), 1.0, glass_material);

  // Left - red diffuse sphere
  auto red_material = create_lambertian(color(1.0, 0.2, 0.2));
  add_sphere(point3(-2.5, 0.7, 0), 0.7, red_material);

  // Right - blue metallic sphere
  auto blue_metal = create_metal(color(0.2, 0.3, 0.8), 0.1);
  add_sphere(point3(2.5, 0.7, 0), 0.7, blue_metal);

  // Back - gold metallic sphere
  auto gold = create_metal(color(0.8, 0.7, 0.2), 0.2);
  add_sphere(point3(0, 0.7, -2.5), 0.7, gold);

  // Front - small purple glass sphere
  auto purple_glass = create_dielectric(1.7);
  add_sphere(point3(0, 0.3, 1.5), 0.3, purple_glass);

  // Small decorative spheres in a circle
  for (int i = 0; i < 8; i++) {
    double angle = i * pi / 4.0;
    double x = 3.5 * std::cos(angle);
    double z = 3.5 * std::sin(angle);

    // Alternate between metal and diffuse
    if (i % 2 == 0) {
      auto mat = create_metal(color(0.8, 0.8, 0.8), 0.0);
      add_sphere(point3(x, 0.3, z), 0.3, mat);
    } else {
      auto mat = create_lambertian(color::random());
      add_sphere(point3(x, 0.3, z), 0.3, mat);
    }
  }
}

void Scene::render_weekend_scene() {
  // Clear any existing objects
  world.clear();

  // Ground - a large gray sphere
  auto ground_material = create_lambertian(color(0.5, 0.5, 0.5));
  add_sphere(point3(0, -1000, 0), 1000, ground_material);

  // Small random spheres
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        if (choose_mat < 0.8) {
          // Diffuse
          auto albedo = color::random() * color::random();
          auto sphere_material = create_lambertian(albedo);
          add_sphere(center, 0.2, sphere_material);
        } else if (choose_mat < 0.95) {
          // Metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          auto sphere_material = create_metal(albedo, fuzz);
          add_sphere(center, 0.2, sphere_material);
        } else {
          // Glass
          auto sphere_material = create_dielectric(1.5);
          add_sphere(center, 0.2, sphere_material);
        }
      }
    }
  }

  // Three large spheres
  auto material1 = create_dielectric(1.5);
  add_sphere(point3(0, 1, 0), 1.0, material1);

  auto material2 = create_lambertian(color(0.4, 0.2, 0.1));
  add_sphere(point3(-4, 1, 0), 1.0, material2);

  auto material3 = create_metal(color(0.7, 0.6, 0.5), 0.0);
  add_sphere(point3(4, 1, 0), 1.0, material3);
}

} // namespace raytracer
