//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "common.h"
#include "Material.h"
#include "Hitable.h"
#include "Ray.h"
#include "Helpers.h"
#include "UnitRandomGenerator.h"

class Metal : public Material {
public:
    Metal(const vec3& a, Float f) : albedo(a) {
        if (f < 1)
            fuzz = f;
        else
            fuzz = 1;
    }
    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz*rng.random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    vec3 albedo;
    Float fuzz;
};
#endif //RAYTRACER_METAL_H
