#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class vec3 {
  public:
    double x, y, z;

    vec3() : x(0), y(0), z(0) {}
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    vec3 operator-() const;

    vec3 &operator+=(const vec3 &v);

    vec3 &operator-=(const vec3 &v);

    vec3 &operator*=(const vec3 &v);

    vec3 &operator/=(const vec3 &v);

    double length() const;

    double length_squared() const;

    static vec3 random();

    static vec3 rand_range(double min, double max);
};

vec3 operator+(const vec3 &u, const vec3 &v);

vec3 operator-(const vec3 &u, const vec3 &v);

vec3 operator*(const vec3 &u, const vec3 &v);

vec3 operator*(double t, const vec3 &v);

vec3 operator*(const vec3 &v, double t);

vec3 operator/(vec3 v, double t);

std::ostream &operator<<(std::ostream &out, const vec3 &v);

double dot(const vec3 &u, const vec3 &v);

vec3 cross(const vec3 &u, const vec3 &v);

vec3 unit_vector(const vec3 &v);

vec3 random_in_unit_sphere();

vec3 random_unit_vector();

vec3 random_on_hemisphere(const vec3 &normal);

using point3 = vec3;

#endif
