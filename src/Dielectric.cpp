//
// Created by Joona on 17/10/2018.
//

#include "raytracer/Dielectric.h"
#include "raytracer/common.h"
#include "raytracer/Helpers.h"


bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    Float ni_per_nt = 1;
    attenuation = {1.0, 1.0, 1.0};
    vec3 refracted;
    Float reflect_probability;
    Float cosine;

    if (dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_per_nt = ref_idx;
        cosine = ref_idx * dot(r_in.unit_direction(), rec.normal);
    }
    else {
        outward_normal = rec.normal;
        ni_per_nt = 1 / ref_idx;
        cosine = -ref_idx * dot(r_in.unit_direction(), rec.normal);
    }

    if (refract(r_in.direction(), outward_normal, ni_per_nt, refracted)) {
        reflect_probability = schlick(cosine, ref_idx);
    }
    else {
        reflect_probability = 1.0;
    }

    if (rng.get_number() < reflect_probability) {
       scattered = Ray(rec.p, reflected);
    }
    else {
        scattered = Ray(rec.p, refracted);
    }
    return true;
}

