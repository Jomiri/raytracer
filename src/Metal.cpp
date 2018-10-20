//
// Created by Joona on 20/10/2018.
//
#include "raytracer/common.h"
#include "raytracer/Metal.h"
#include "raytracer/Helpers.h"

Metal::Metal(const vec3& a, Float f) : albedo(a), fuzz(f < 1 ? f : 1) { }

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const {
    vec3 refl = reflected(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.point, refl + fuzz*rng.random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}