//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "common.h"
#include "Ray.h"

class Camera {
public:
    Camera(vec3 lookfrom, vec3 lookat, vec3 vup, Float vfov,
            Float aspect, Float aperture, Float focus_dist);

    Ray get_ray(Float u, Float v) const;

    vec3 upper_left_corner {0, 0, 0};
    vec3 horizontal  {0, 0, 0};
    vec3 vertical {0, 0, 0};
    vec3 origin {0, 0, 0};
    vec3 u, v, w;
    Float lens_radius = 0;

};

#endif //RAYTRACER_CAMERA_H
