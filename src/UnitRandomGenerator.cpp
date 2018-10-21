//
// Created by Joona on 16/10/2018.
//

#include "raytracer/common.h"
#include "raytracer/UnitRandomGenerator.h"


namespace rng {
    Float get() {
        static thread_local std::default_random_engine generator;
        static std::uniform_real_distribution<Float> distribution(0.0, 1.0);
        return distribution(generator);
    }


    vec3 random_in_unit_sphere() {
        vec3 p;
        do {
            p = 2.0 * vec3(get(), get(), get()) - vec3(1, 1, 1);
        } while (p.len_squared() >= 1.0);
        return p;
    }

    vec3 random_in_unit_disk() {
        vec3 p;
        do {
            p = 2.0 * vec3(get(), get(), 0) - vec3(1, 1, 0);
        } while (dot(p,p) >= 1.0);
        return p;
    }
}
