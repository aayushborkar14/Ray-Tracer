#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
  private:
    color albedo;
    double p;

  public:
    lambertian(const color &a, double p = 1.00) : albedo(a), p{p} {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                 ray &scattered) const override {
        if (random_double() > p)
            return false;
        vec3 scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = {rec.p, scatter_direction};
        attenuation = albedo / p;
        return true;
    }
};

class metal : public material {
  private:
    color albedo;

  public:
    metal(const color &a) : albedo(a) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                 ray &scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = {rec.p, reflected};
        attenuation = albedo;
        return true;
    }
};

#endif
