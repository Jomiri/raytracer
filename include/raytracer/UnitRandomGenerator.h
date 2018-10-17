//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_RANDOMGENERATOR_H
#define RAYTRACER_RANDOMGENERATOR_H

#include "common.h"
#include <random>

class UnitRandomGenerator {
public:
    double get_number() { return distribution(generator); }
    vec3 random_in_unit_sphere();

private:
    std::default_random_engine generator;
    std::uniform_real_distribution<Float> distribution{0.0, 1.0};
};

extern UnitRandomGenerator rng;



#endif //RAYTRACER_RANDOMGENERATOR_H
