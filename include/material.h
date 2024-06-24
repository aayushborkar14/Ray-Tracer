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
    double fuzz_factor;

  public:
    metal(const color &a, double fuzz = 0)
        : albedo(a), fuzz_factor(min(fuzz, 1.0)) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                 ray &scattered) const override {
        vec3 reflected =
            unit_vector(reflect(unit_vector(r_in.direction()), rec.normal)) +
            (fuzz_factor * random_unit_vector());
        scattered = {rec.p, reflected};
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};

class dielectric : public material {
  private:
    double refractive_index;

  public:
    dielectric(double refractive_index) : refractive_index(refractive_index) {}

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                 ray &scattered) const override {
        double ri =
            rec.front_face ? (1.0 / refractive_index) : refractive_index;
        vec3 refracted = refract(unit_vector(r_in.direction()), rec.normal, ri);
        scattered = {rec.p, refracted};
        attenuation = {1.0, 1.0, 1.0};
        return true;
    }
};

#endif
