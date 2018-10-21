//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "Common.h"
#include "Ray.h"
#include "Hitable.h"
#include "Random.h"

class Material {
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
    virtual ~Material() = default;
};
#endif //RAYTRACER_MATERIAL_H
