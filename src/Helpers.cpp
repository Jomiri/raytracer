//
// Created by Joona on 16/10/2018.
//

#include "Common.h"
#include "Helpers.h"

vec3 reflected(const vec3 &v, const vec3 &n) {
    return v - 2*dot(v, n) * n;
}

bool refract(const vec3& v, const vec3& n, Float ni_per_nt, vec3& refracted) {
    vec3 u0 = unit_vector(v);
    Float dt = dot(u0, n);
    Float discriminant = 1.0 - ni_per_nt * ni_per_nt * (1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_per_nt*(u0 - n*dt) - n*sqrt(discriminant);
        return true;
    }
    return false;
}

Float schlick(Float cosine, Float ref_idx) {
    Float r = (1-ref_idx) / (1+ref_idx);
    Float R = r*r;
    return R + (1-R)*pow(1-cosine, 5);
}
