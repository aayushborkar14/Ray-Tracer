#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <numbers>

using std::make_shared;
using std::max;
using std::min;
using std::shared_ptr;
using std::sqrt;
using std::numbers::pi;

constexpr double infinity = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

inline double rand_range(double min, double max) {
    return min + (max - min) * random_double();
}

#endif
