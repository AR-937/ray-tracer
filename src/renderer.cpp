#include "renderer.h"
#include "color.h"
#include "material.h"
#include "utilities.h"
#include <iomanip>
#include <iostream>

namespace raytracer {

void Renderer::render(const hittable &world, const Camera &camera) {
  // Initialize camera
  Camera cam = camera;
  cam.initialize();

  int image_height = cam.get_image_height();
  double pixel_samples_scale = 1.0 / samples_per_pixel;

  // Output image header once at the beginning
  {
    std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << "P3\n" << cam.image_width << ' ' << image_height << "\n255\n";
  }

  // Multi-threaded rendering setup
  const int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  std::atomic<int> next_row{0};
  std::atomic<int> rows_remaining{image_height};

  // Start threads
  for (int t = 0; t < num_threads; ++t) {
    threads.emplace_back([this, &world, &cam, &next_row, &rows_remaining,
                          image_height, pixel_samples_scale]() {
      std::vector<std::string> pixel_rows;

      while (true) {
        int j = next_row.fetch_add(1);
        if (j >= image_height)
          break;

        // Record the current row's pixels
        std::stringstream row_stream;

        for (int i = 0; i < cam.image_width; i++) {
          color pixel_color(0, 0, 0);
          for (int sample = 0; sample < samples_per_pixel; sample++) {
            ray r = cam.get_ray(i, j);
            pixel_color += ray_color(r, max_depth, world);
          }

          // Write pixel to the string stream
          write_color(row_stream, pixel_samples_scale * pixel_color);
        }

        // Update progress safely
        int remaining = rows_remaining.fetch_sub(1) - 1;

        // Output row and update progress
        {
          std::lock_guard<std::mutex> lock(output_mutex);
          std::cout << row_stream.str();
          std::clog << "\rScanlines remaining: " << remaining << "   "
                    << std::flush;
        }
      }
    });
  }

  // Wait for all threads to complete
  for (auto &thread : threads) {
    thread.join();
  }

  std::clog << "\rRendering complete!                 \n";
}

color Renderer::ray_color(const ray &r, int depth,
                          const hittable &world) const {
  // If we've exceeded the ray bounce limit, no more light is gathered
  if (depth <= 0)
    return color(0, 0, 0);

  hit_record rec;

  // Use a small offset to avoid "shadow acne" caused by numerical precision
  // issues
  if (world.hit(r, interval(0.001, infinity), rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, depth - 1, world);
    return color(0, 0, 0);
  }

  // If the ray hits nothing, return the background color (a blue-to-white
  // gradient)
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

} // namespace raytracer
