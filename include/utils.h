#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <limits>
#include <memory>
#include <numbers>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;
using std::numbers::pi;

const double infinity = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#endif
