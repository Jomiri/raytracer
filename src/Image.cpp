//
// Created by Joona on 13/10/2018.
//

#include <fstream>
#include "raytracer/common.h"
#include "raytracer/Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image/stb_image_write.h"


Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    pixels = std::vector<vec3>(width * height);
}

int Image::get_height() const {
    return height;
}

int Image::get_width() const {
    return width;
}

void Image::set_pixel_at(int x, int y, vec3 pixel) {
    pixels.at(x + y*width) = pixel;
}

vec3 Image::get_pixel_at(int x, int y) const {
    return pixels.at(x + y*width);
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

void Image::to_png(const std::string& file_name) const {
    std::vector<unsigned char> data;
    data.reserve(4*width*height);
    for (const auto& p : pixels) {
        data.push_back(static_cast<unsigned char>(255.99 * p.x));
        data.push_back(static_cast<unsigned char>(255.99 * p.y));
        data.push_back(static_cast<unsigned char>(255.99 * p.z));
        data.push_back(255);
    }
    stbi_write_png(file_name.c_str(), width, height, 4, data.data(), 4*width);
}

void Image::gamma_correct() {
    for (auto& px : pixels) {
        px = vec3(sqrt(px.x), sqrt(px.y), sqrt(px.z));
    }
}
