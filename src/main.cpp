#include <iostream>
#include "../include/raytracer/vector3d.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    vec3 v{};
    vec3 v2{1,2,3};
    std::cout << v << std::endl;
    std::cout << unit_vector(v2) << std::endl;
    return 0;
}