#include "color.h"
#include "progress_bar.h"
#include "ray.h"
#include "vec3.h"
#include <algorithm>
#include <iostream>

bool hit_sphere(const point3 &center, double radius, const ray &r) {
    point3 Q = r.origin();
    vec3 d = r.direction();
    double a = dot(d, d);
    double b = -2 * dot(d, center - Q);
    double c = dot(center - Q, center - Q) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}

color ray_color(const ray &r) {
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
        return color(0.36, 0.08, 0.55);
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(0.12, 0.15, 0.34) + t * color(0.23, 0.49, 0.44);
}

int main() {

    // Image

    const double aspect_ratio = 16.0 / 9.0;
    const int IMAGE_WIDTH = 1280;

    // IMAGE_HEIGHT is calculated based on the aspect ratio, and IMAGE_WIDTH of
    // the image, and is at least 1.
    const int IMAGE_HEIGHT =
        std::max(static_cast<int>(IMAGE_WIDTH / aspect_ratio), 1);

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * static_cast<double>(IMAGE_WIDTH) / IMAGE_HEIGHT;
    point3 camera_center{0, 0, 0};

    // Horizontal and vertical vectors of viewport
    vec3 viewport_u{viewport_width, 0, 0};
    vec3 viewport_v{0, -viewport_height, 0};

    // Pixel delta vectors
    vec3 pixel_delta_u = viewport_u / IMAGE_WIDTH;
    vec3 pixel_delta_v = viewport_v / IMAGE_HEIGHT;

    // Upper left pixel of the viewport
    point3 viewport_upper_left = camera_center - viewport_u / 2 -
                                 viewport_v / 2 - vec3(0, 0, focal_length);
    point3 pixel00_loc =
        viewport_upper_left + pixel_delta_u / 2 + pixel_delta_v / 2;

    // Setup ProgressBar on std::clog
    ProgressBar bar(std::clog);

    // Render

    std::cout << "P3\n"
              << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n"
              << "255\n";
    for (int j = 0; j < IMAGE_HEIGHT; j++) {
        for (int i = 0; i < IMAGE_WIDTH; i++) {
            point3 pixel_center =
                pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
            vec3 ray_direction = pixel_center - camera_center;
            ray r{camera_center, ray_direction};
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
        bar.update((static_cast<float>(j) + 1) / IMAGE_HEIGHT);
    }
    bar.completed();
}
