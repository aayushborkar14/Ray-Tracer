#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "progress_bar.h"
#include "utils.h"
#include "vec3.h"
#include <iostream>

class camera {
  private:
    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double pixel_samples_scale;
    vec3 u, v, w;

    void initialize() {
        image_height = max(static_cast<int>(image_width / aspect_ratio), 1);

        center = lookfrom;

        // Viewport dimensions
        double focal_length = (lookfrom - lookat).length();
        double theta = degrees_to_radians(vfov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h * focal_length;
        double viewport_width =
            viewport_height * static_cast<double>(image_width) / image_height;

        // Calculate u, v, w
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = unit_vector(cross(w, u));

        // Horizontal and vertical vectors of viewport
        vec3 viewport_u{u * viewport_width};
        vec3 viewport_v{-v * viewport_height};

        // Pixel delta vectors
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        point3 viewport_upper_left =
            center - viewport_u / 2 - viewport_v / 2 - w * focal_length;
        pixel00_loc =
            viewport_upper_left + pixel_delta_u / 2 + pixel_delta_v / 2;

        pixel_samples_scale = 1.0 / samples_per_pixel;
    }

    color ray_color(const ray &r, int depth, const hittable &world) const {
        if (depth <= 0)
            return {0, 0, 0};

        hit_record rec;

        if (world.hit(r, {0.001, infinity}, rec)) {
            ray scattered{};
            color attenuation{};
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return {0, 0, 0};
        }

        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
    }

    vec3 sample_square() const {
        return {random_double() - 0.5, random_double() - 0.5, 0};
    }

    ray get_ray(int i, int j) const {
        vec3 offset = sample_square();
        point3 pixel_sample = pixel00_loc + pixel_delta_u * (i + offset.x) +
                              pixel_delta_v * (j + offset.y);
        return {center, pixel_sample - center};
    }

  public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;
    double vfov = 90;

    point3 lookfrom = {0, 0, 0};
    point3 lookat = {0, 0, -1};
    vec3 vup = {0, 1, 0};

    void render(const hittable &world) {
        initialize();
        // Setup ProgressBar on std::clog
        ProgressBar bar(std::clog);

        std::cout << "P6\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                color pixel_color{0, 0, 0};
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_color * pixel_samples_scale);
            }
            bar.update((static_cast<float>(j) + 1) / image_height);
        }
        bar.completed();
    };
};

#endif
