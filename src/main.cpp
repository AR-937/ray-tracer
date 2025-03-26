#include "camera.h"
#include "renderer.h"
#include "scene.h"

using namespace raytracer;

int main() {
  // Create a scene
  Scene scene;

  // Create the original scene from "Ray Tracing in One Weekend"
  scene.create_weekend_scene();

  // Configure camera for the weekend scene
  Camera camera;
  camera.aspect_ratio = 16.0 / 9.0;
  camera.image_width =
      1200; // Start with a moderate resolution for faster feedback

  // Position camera to view the scene from a distance
  camera.lookfrom = point3(13, 2, 3);
  camera.lookat = point3(0, 0, 0);
  camera.vup = vec3(0, 1, 0);

  // Use a moderate field of view
  camera.vfov = 20;

  // Add some depth of field for artistic effect
  camera.defocus_angle = 0.6;
  camera.focus_dist = 10.0;

  // Configure renderer with moderate quality settings
  Renderer renderer;
  renderer.samples_per_pixel = 10; // Increase for final renders
  renderer.max_depth = 20;         // Sufficient for most materials

  // Render the scene
  renderer.render(scene.get_world(), camera);

  return 0;
}
