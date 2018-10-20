//
// Created by Joona on 14/10/2018.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "common.h"

struct Ray {
    Ray () = default;
    Ray(const vec3& origin, const vec3& direction): A{origin}, B{direction} {}
    const vec3& origin() const { return A; }
    const vec3& direction() const { return B; }
    vec3 unit_direction() const { return unit_vector(direction()); }
    vec3 point_at_parameter(Float t) const { return A + B*t; }


    vec3 A;
    vec3 B;
};
#endif //RAYTRACER_RAY_H
