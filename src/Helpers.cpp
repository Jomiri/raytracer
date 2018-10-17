//
// Created by Joona on 16/10/2018.
//

#include "raytracer/common.h"
#include "raytracer/Helpers.h"

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v, n) * n;
}
