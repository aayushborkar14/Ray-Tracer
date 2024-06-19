#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

double linear_to_gamma(double linear);

void write_color(std::ostream &out, const color &pixel_color);

#endif
