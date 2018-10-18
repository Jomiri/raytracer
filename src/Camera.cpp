//
// Created by Joona on 18/10/2018.
//


#include "raytracer/common.h"
#include "raytracer/Camera.h"
#include "raytracer/UnitRandomGenerator.h"


Camera::Camera(vec3 lookfrom, vec3 lookat, vec3 vup,
        Float vfov, Float aspect, Float aperture, Float focal_length) {

    lens_radius = aperture / 2;
    Float theta = vfov * pi/180;
    Float half_height = tan(theta/2);
    Float half_width = aspect * half_height;
    origin = lookfrom;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
    upper_left_corner =  origin + focal_length*(-half_width*u + half_height*v - w);
    horizontal = 2*half_width*u * focal_length;
    vertical = 2*half_height*v * focal_length;
}

Ray Camera::get_ray(Float s, Float t) {
    vec3 rd = lens_radius*rng.random_in_unit_disk();
    vec3 offset = u * rd.x + v * rd.y;
    return {origin + offset, upper_left_corner + s * horizontal + t * vertical - origin - offset};
}