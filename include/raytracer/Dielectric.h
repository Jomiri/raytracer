//
// Created by Joona on 17/10/2018.
//

#ifndef RAYTRACER_DIELECTRIC_H
#define RAYTRACER_DIELECTRIC_H

#include "common.h"
#include "Material.h"
#include "Ray.h"

class Dielectric : public Material {
public:
    explicit Dielectric(Float ri) : ref_idx(ri) {}
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const override;

    Float ref_idx = 0;
};


#endif //RAYTRACER_DIELECTRIC_H
