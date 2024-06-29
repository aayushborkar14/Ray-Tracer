#include "vec3.h"
#include "utils.h"
#include <cmath>
#include <iostream>

vec3 vec3::operator-() const { return {-x, -y, -z}; }

vec3 &vec3::operator+=(const vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3 &vec3::operator-=(const vec3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3 &vec3::operator*=(const vec3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

vec3 &vec3::operator/=(const vec3 &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

double vec3::length() const { return std::sqrt(length_squared()); }

double vec3::length_squared() const { return x * x + y * y + z * z; }

bool vec3::near_zero() const {
    const double s = 1e-8;
    return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
}

vec3 vec3::random() {
    return {random_double(), random_double(), random_double()};
}

vec3 vec3::rand_range(double min, double max) {
    return {::rand_range(min, max), ::rand_range(min, max),
            ::rand_range(min, max)};
}

vec3 operator+(const vec3 &u, const vec3 &v) {
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return {u.x * v.x, u.y * v.y, u.z * v.z};
}

vec3 operator*(double t, const vec3 &v) { return {t * v.x, t * v.y, t * v.z}; }

vec3 operator*(const vec3 &v, double t) { return t * v; }

vec3 operator/(vec3 v, double t) { return {v.x / t, v.y / t, v.z / t}; }

std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

double dot(const vec3 &u, const vec3 &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

vec3 cross(const vec3 &u, const vec3 &v) {
    return {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x};
}

vec3 unit_vector(const vec3 &v) { return v / v.length(); }

vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p = vec3::rand_range(-1, 1);
        if (p.length_squared() < 1 && p.length_squared() > 0.1)
            return p;
    }
}

vec3 random_unit_vector() { return unit_vector(random_in_unit_sphere()); }

vec3 random_on_hemisphere(const vec3 &normal) {
    vec3 random_on_sphere = random_unit_vector();
    if (dot(random_on_sphere, normal) > 0.0)
        return random_on_sphere;
    return -random_on_sphere;
}

vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * dot(v, n) * n; }

vec3 refract(const vec3 &v, const vec3 &n, double eta_ratio) {
    double cos = min(dot(-v, n), 1.0);
    vec3 r_perp = eta_ratio * (v + cos * n);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_perp.length_squared())) * n;
    return r_perp + r_parallel;
}
