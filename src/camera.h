#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

namespace raytracer {

class Camera {
public:
  // image settings
  double aspect_ratio = 1.0; // ratio of image width over height
  int image_width = 100;     // rendered image width in pixel count

  // camera settings
  double vfov = 90;
  point3 lookfrom = point3(0, 0, 0);
  point3 lookat = point3(0, 0, -1);
  vec3 vup = vec3(0, 1, 0);

  // defocus blur settings
  double defocus_angle = 0; // variation angle of rays through each pixel
  double focus_dist =
      10; // distance from camera lookfrom point to plane of perfect focus

  Camera() = default;

  // initialize the camera params
  void initialize();

  [[nodiscard]] ray get_ray(int i, int j) const;

  [[nodiscard]] int get_image_height() const {
    return static_cast<int>(image_width / aspect_ratio);
  }

private:
  int image_height = 0;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;
  vec3 u, v, w;
  vec3 defocus_disk_u;
  vec3 defocus_disk_v;

  // helper methods
  [[nodiscard]] vec3 sample_square() const;
  [[nodiscard]] point3 defocus_disk_sample() const;
};

} // namespace raytracer

#endif
