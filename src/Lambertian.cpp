//
// Created by Joona on 20/10/2018.
//

#include "raytracer/common.h"
#include "raytracer/Lambertian.h"

Lambertian::Lambertian(const vec3& a) : albedo(a) {}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const {
    scattered = Ray(rec.point, rec.normal + rng::random_in_unit_sphere());
    attenuation = albedo;
    return true;
}
