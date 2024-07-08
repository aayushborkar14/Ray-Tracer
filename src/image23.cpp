#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "utils.h"
#include "vec3.h"
#include <memory>

int main() {
    // World
    hittable_list world;

    shared_ptr<material> material_ground =
        make_shared<lambertian>(color(0.4, 0.4, 0.4));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, material_ground));

    // Smaller Spheres
    for (int i = -11; i < 11; i++)
        for (int j = -11; j < 11; j++) {
            double sample_material = random_double();
            point3 center{i + 0.8 * random_double(), 0.2,
                          j + 0.8 * random_double()};

            if ((center - point3{4, 0.2, 0}).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (sample_material < 0.8) {
                    color albedo = color::random();
                    double p = rand_range(0.7, 1);
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else if (sample_material < 0.9) {
                    color albedo = color::rand_range(0.5, 1);
                    double fuzz = rand_range(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }

    // Bigger Spheres
    shared_ptr<material> material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3{0, 1, 0}, 1.0, material1));
    shared_ptr<material> material2 =
        make_shared<lambertian>(color{0.4, 0.2, 0.1}, 0.9);
    world.add(make_shared<sphere>(point3{-4, 1, 0}, 1.0, material2));
    shared_ptr<material> material3 =
        make_shared<metal>(color{0.7, 0.6, 0.5}, 0.0);
    world.add(make_shared<sphere>(point3{4, 1, 0}, 1.0, material3));

    // Camera
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1280;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = {15, 2, 4};
    cam.lookat = {0, 0, 0};
    cam.vup = {0, 1, 0};

    cam.defocus_angle = 0.0;
    cam.focus_dist = 10.0;

    // Render
    cam.render(world);
}
