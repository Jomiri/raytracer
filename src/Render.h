//
// Created by Joona on 21/10/2018.
//

#ifndef RAYTRACER_RENDER_H
#define RAYTRACER_RENDER_H

#include "Hitable.h"
#include "Camera.h"
#include "Image.h"

void render(const Hitable *const  world, const Camera& cam, int num_samples, Image& im);
void async_render(const Hitable *const world, const Camera& cam, int num_samples, Image& out);

#endif //RAYTRACER_RENDER_H
