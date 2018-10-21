//
// Created by Joona on 14/10/2018.
//

#ifndef RAYTRACER_HITABLE_H
#define RAYTRACER_HITABLE_H

#include "Common.h"
#include "Ray.h"
#include "Random.h"

class Material;

struct HitRecord {
    Float t {0};
    vec3 point;
    vec3 normal;
    Material* mat_ptr = nullptr;
    HitRecord() = default;
};

struct Interval {
    Float min;
    Float max;
    bool contains(const Float x) const {
        return x > min && x < max;
    }
};

class Hitable {
public:
    virtual bool hit(const Ray& r, const Interval& t_limits, HitRecord& rec) const = 0;
    virtual ~Hitable() = default;
};

#endif //RAYTRACER_HITABLE_H
