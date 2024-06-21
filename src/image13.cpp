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

    shared_ptr<lambertian> material_ground =
        make_shared<lambertian>(color{0.8, 0.8, 0.0}, 0.8);
    shared_ptr<lambertian> material_center =
        make_shared<lambertian>(color{0.1, 0.2, 0.5}, 0.8);
    shared_ptr<metal> material_left = make_shared<metal>(color{0.2, 0.2, 0.2});
    shared_ptr<metal> material_right = make_shared<metal>(color{0.8, 0.6, 0.2});

    world.add(make_shared<sphere>(point3{0, -100.5, -1}, 100, material_ground));
    world.add(make_shared<sphere>(point3{0, 0, -1.5}, 0.5, material_center));
    world.add(make_shared<sphere>(point3{-1, 0, -1}, 0.5, material_left));
    world.add(make_shared<sphere>(point3{1, 0, -1}, 0.5, material_right));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;

    // Render
    cam.render(world);
}
