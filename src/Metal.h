//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "Common.h"
#include "Material.h"
#include "Hitable.h"
#include "Ray.h"
#include "Helpers.h"
#include "Random.h"

class Metal : public Material {
public:
    Metal(const vec3& a, Float f);
    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const override;

private:
    vec3 albedo;
    Float fuzz;
};
#endif //RAYTRACER_METAL_H
