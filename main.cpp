#include "color.h"
#include "vec3.h"
#include <iostream>

int main() {
    const int IMAGE_HEIGHT = 1200;
    const int IMAGE_WIDTH = 1200;

    std::cout << "P3\n"
              << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n"
              << "255\n";
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        std::clog << (100.00 * i) / IMAGE_HEIGHT << "% done\n" << std::flush;
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            auto pixel_color = color(double(j) / (IMAGE_WIDTH - 1),
                                     double(i) / (IMAGE_HEIGHT - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "100% done\n" << std::flush;
}
