#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}

    interval(double min, double max) : min(min), max(max) {}

    double size() const { return max - min; }

    bool contains(double x) const { return min <= x && x <= max; }

    bool surrounds(const interval &other) const {
        return min <= other.min && max >= other.max;
    }

    bool surrounds(double y) const { return min <= y && y <= max; }

    static const interval empty, universe;
};

const interval interval::empty{+infinity, -infinity};
const interval interval::universe{-infinity, infinity};

#endif
