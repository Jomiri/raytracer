//
// Created by Joona on 13/10/2018.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include "vector3d.h"
#include <vector>


class Image {
public:
    Image () = default;
    Image (int width, int height);

    void set_pixel_at(int x, int y, const vec3 pixel);
    void to_ppm(const std::string& file_name) const;


private:
    int height = 1;
    int width = 1;
    std::vector<vec3> pixels;
};


#endif //RAYTRACER_IMAGE_H
