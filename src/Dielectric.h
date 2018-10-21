//
// Created by Joona on 17/10/2018.
//

#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H

#include "Common.h"
#include "Material.h"
#include "Ray.h"

class Dielectric : public Material {
public:
    explicit Dielectric(Float ri) : ref_idx(ri) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& atten, Ray& scattered) const override;

private:
    Float ref_idx = 1;
    const vec3 attenuation {1.0, 1.0, 1.0};
};


#endif //RAYTRACER_DIELECTRIC_H
