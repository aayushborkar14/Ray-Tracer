#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include <cmath>

class sphere : public hittable {
  private:
    point3 center;
    double radius;

  public:
    sphere(const point3 &center, double radius)
        : center(center), radius(fmax(radius, 0)) {}

    bool hit(const ray &r, double t_min, double t_max,
             hit_record &rec) const override {
        vec3 oc = center - r.origin();
        vec3 d = r.direction();
        double a = d.length_squared();
        double h = dot(d, oc);
        double c = oc.length_squared() - radius * radius;
        double discriminant = h * h - a * c;

        if (discriminant < 0)
            return false;
        double sqrtd = sqrt(discriminant);

        double root = (h - sqrtd) / a;
        if (root <= t_min || root >= t_max) {
            root = (h + sqrtd) / a;
            if (root <= t_min || root >= t_max)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};

#endif
