//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_RANDOMGENERATOR_H
#define RAYTRACER_RANDOMGENERATOR_H

#include "Common.h"
#include <random>

namespace rng {
    Float get();
    vec3 random_in_unit_sphere();
    vec3 random_in_unit_disk();
}




#endif //RAYTRACER_RANDOMGENERATOR_H
