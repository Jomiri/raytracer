//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "common.h"
#include "Material.h"
#include "Ray.h"
#include "Hitable.h"
#include "UnitRandomGenerator.h"

class Lambertian : public Material {
public:
    explicit Lambertian(const vec3& a);
    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const override;

private:
    vec3 albedo;
};
#endif //RAYTRACER_LAMBERTIAN_H
