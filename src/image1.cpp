#include "color.h"
#include "progress_bar.h"
#include "vec3.h"
#include <iostream>

int main() {
    // Image

    const int IMAGE_HEIGHT = 720;
    const int IMAGE_WIDTH = 720;

    // Setup ProgressBar on std::clog
    ProgressBar bar(std::clog);

    // Render

    std::cout << "P3\n"
              << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n"
              << "255\n";
    for (int j = 0; j < IMAGE_HEIGHT; j++) {
        for (int i = 0; i < IMAGE_WIDTH; i++) {
            auto pixel_color =
                color(static_cast<double>(i) / (IMAGE_WIDTH - 1),
                      static_cast<double>(j) / (IMAGE_HEIGHT - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
        bar.update((static_cast<float>(j) + 1) / IMAGE_HEIGHT);
    }
    bar.completed();
}
