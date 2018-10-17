//
// Created by Joona on 14/10/2018.
//
#include "raytracer/common.h"
#include "raytracer/Sphere.h"

bool Sphere::hit(const Ray& r, const Interval& t_limits, HitRecord& rec) const {
    vec3 oc = r.origin() - center;
    Float a = dot(r.direction(), r.direction());
    Float b = dot(oc, r.direction());
    Float c = dot(oc, oc) - radius * radius;
    Float discriminant = b * b - a * c;
    if (discriminant < 0) {
        return false;
    }

    Float solution = (-b - sqrt(b * b - a * c)) / a;
    if (t_limits.within_limits(solution)) {
        fill_hit_record(r, solution, rec);
        return true;
    }
    Float solution2 = (-b + sqrt(b * b - a * c)) / a;
    if (t_limits.within_limits(solution2)) {
        fill_hit_record(r, solution2, rec);
        return true;
    }
    return false;
}

void Sphere::fill_hit_record(const Ray &r, const Float t, HitRecord &rec) const {
    rec.t = t;
    rec.p = r.point_at_parameter(t);
    rec.normal = (rec.p - center) / radius;
    rec.mat_ptr = material;
}


