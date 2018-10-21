//
// Created by Joona on 21/10/2018.
//

#ifndef RAYTRACER_WORLDS_H
#define RAYTRACER_WORLDS_H

#include "Common.h"
#include "Hitable.h"
#include "Scene.h"

namespace Worlds {
    const Hitable *const example_scene(Scene& scene);
    const Hitable *const random_scene(Scene& sc);
    const Hitable *const animation(Scene& scene, Float t);
    const Hitable *const atom_animation(Scene& scene, Float t);
}
#endif //RAYTRACER_WORLDS_H
