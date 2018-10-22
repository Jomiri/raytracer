//
// Created by Joona on 17/10/2018.
//

#include "Dielectric.h"
#include "Common.h"
#include "Helpers.h"


bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, vec3& atten, Ray& scattered) const {
    atten = attenuation;
    vec3 outward_normal = rec.normal;
    Float ni_per_nt = 1.0 / ref_idx;
    if (dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_per_nt = ref_idx;
    }

    const Float cosine {-ref_idx * dot(r_in.unit_direction(), outward_normal)};
    Float reflect_probability {1.0};
    vec3 refracted;
    if (refract(r_in.direction(), outward_normal, ni_per_nt, refracted))
        reflect_probability = schlick(cosine, ref_idx);

    if (rng::get() < reflect_probability)
        scattered = {rec.point, reflected(r_in.direction(), rec.normal)};
    else
        scattered = {rec.point, refracted};
    return true;
}

