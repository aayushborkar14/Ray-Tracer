#include "color.h"
#include "interval.h"

void write_color(std::ostream &out, const color &pixel_color) {
    auto r = pixel_color.x;
    auto g = pixel_color.y;
    auto b = pixel_color.z;

    static const interval intensity{0.0, 0.999};
    int rbyte = static_cast<int>(256 * intensity.clamp(r));
    int gbyte = static_cast<int>(256 * intensity.clamp(g));
    int bbyte = static_cast<int>(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
