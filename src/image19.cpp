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

    double r = cos(pi / 4);

    shared_ptr<lambertian> material_left =
        make_shared<lambertian>(color(0, 0, 1));
    shared_ptr<lambertian> material_right =
        make_shared<lambertian>(color(0, 1, 1));

    world.add(make_shared<sphere>(point3(-r, 0, -1), r, material_left));
    world.add(make_shared<sphere>(point3(r, 0, -1), r, material_right));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.vfov = 90;

    // Render
    cam.render(world);
}
