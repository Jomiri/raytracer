//
// Created by Joona on 14/10/2018.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "common.h"
#include "Hitable.h"

class Sphere: public Hitable {
public:
    Sphere() = default;
    Sphere(vec3 c, Float r, Material* mat_ptr): center{c}, radius(r), material(mat_ptr) {};
    bool hit(const Ray& r, const  Interval& t_limits, HitRecord& rec) const override;


private:
    void fill_hit_record(const Ray& r, Float t, HitRecord& rec) const;

    vec3 center {0, 0, 0};
    Float radius {0};
    Material* material {nullptr};
};
#endif //RAYTRACER_SPHERE_H
