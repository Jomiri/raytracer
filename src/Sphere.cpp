//
// Created by Joona on 14/10/2018.
//
#include "Common.h"
#include "Sphere.h"

bool Sphere::hit(const Ray& r, const Interval& t_limits, HitRecord& rec) const {
    const vec3 oc = r.origin() - center;
    const Float a = dot(r.direction(), r.direction());
    const Float b = dot(oc, r.direction());
    const Float c = dot(oc, oc) - radius * radius;
    const Float discriminant = b * b - a * c;
    if (discriminant < 0) {
        return false;
    }

    const Float t1 = (-b - sqrt(discriminant)) / a;
    if (t_limits.contains(t1)) {
        fill_hit_record(r, t1, rec);
        return true;
    }
    const Float t2 = (-b + sqrt(discriminant)) / a;
    if (t_limits.contains(t2)) {
        fill_hit_record(r, t2, rec);
        return true;
    }
    return false;
}

void Sphere::fill_hit_record(const Ray &r, const Float t, HitRecord &rec) const {
    rec.t = t;
    rec.point = r.point_at_parameter(t);
    rec.normal = (rec.point - center) / radius;
    rec.mat_ptr = material;
}


