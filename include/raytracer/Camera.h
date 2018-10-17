//
// Created by Joona on 16/10/2018.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "common.h"
#include "Ray.h"

class Camera {
public:

    Ray get_ray(Float u, Float v) {
        return {origin, upper_left_corner + u * horizontal + v * vertical - origin};
    }

    vec3 upper_left_corner {-2.0, 1.0, -1.0};
    vec3 horizontal {4.0, 0, 0};
    vec3 vertical {0, 2.0, 0};
    vec3 origin {0, 0, 0};

};

#endif //RAYTRACER_CAMERA_H
