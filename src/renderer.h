#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace raytracer {

class Renderer {
public:
    // Rendering settings
    int samples_per_pixel = 10;     // Count of random samples for each pixel
    int max_depth = 10;             // Maximum number of ray bounces into scene

    Renderer() = default;

    // Render the scene using the provided camera
    void render(const hittable& world, const Camera& camera);

private:
    // Helper methods
    [[nodiscard]] color ray_color(const ray& r, int depth, const hittable& world) const;
    void render_rows(const hittable& world, const Camera& camera, 
                     std::atomic<int>& next_row, int image_height);

    std::mutex output_mutex;        // Mutex for thread-safe output
};

} // namespace raytracer

#endif 