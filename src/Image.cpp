//
// Created by Joona on 13/10/2018.
//

#include "raytracer/common.h"
#include <fstream>
#include "raytracer/Image.h"


Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    pixels = std::vector<vec3>(width * height);
}

void Image::set_pixel_at(int x, int y, vec3 pixel) {
    pixels.at(x + y*width) = pixel;
}

void Image::to_ppm(const std::string &file_name) const {
    std::ofstream os {file_name};
    os << "P3" << std::endl;
    os << width << " " << height << std::endl;
    os << "255" << std::endl;

    for (const auto& p : pixels) {
        int ir = int(255.99 * p.x);
        int ig = int(255.99 * p.y);
        int ib = int(255.99 * p.z);
        os << ir << " " << ig << " " << ib << std::endl;
    }

}
