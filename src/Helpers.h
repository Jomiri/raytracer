//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_HELPERS_H
#define RAYTRACER_HELPERS_H

#include "Common.h"

vec3 reflected(const vec3 &v, const vec3 &n);
bool refract(const vec3& v, const vec3& n, Float ni_per_nt, vec3& refracted);
Float schlick(Float cosine, Float ref_idx);
#endif //RAYTRACER_HELPERS_H
