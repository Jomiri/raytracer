//
// Created by Joona on 13/10/2018.
//

#include <fstream>
#include "Common.h"
#include "Image.h"

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
        auto ir = static_cast<int>(255.99 * p.x);
        auto ig = static_cast<int>(255.99 * p.y);
        auto ib = static_cast<int>(255.99 * p.z);
        os << ir << " " << ig << " " << ib << std::endl;
    }
}

void Image::to_png(const std::string& file_name) const {
    std::vector<unsigned char> data;
    constexpr int num_channels = 4;
    data.reserve(num_channels*width*height);
    for (const auto& p : pixels) {
        data.push_back(static_cast<unsigned char>(255.99 * p.x)); // red
        data.push_back(static_cast<unsigned char>(255.99 * p.y)); // green
        data.push_back(static_cast<unsigned char>(255.99 * p.z)); // blue
        data.push_back(255); // alpha
    }
    stbi_write_png(file_name.c_str(), width, height, 4, data.data(), 4*width);
}

void Image::gamma_correct() {
    for (auto& px : pixels) {
        px = vec3(sqrt(px.x), sqrt(px.y), sqrt(px.z));
    }
}

/* After this operation, "out" contains the average of "images"
 * Inefficient, but that does not matter here.
 */
void average_images(const std::vector<Image> &images, Image &out) {
    const size_t n_images = images.size();
    const int width = out.get_width();
    const int height = out.get_height();
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            vec3 col {0, 0, 0};
            for (int k = 0; k < n_images; k++) {
                col += images[k].get_pixel_at(i, j);
            }
            col /= Float(n_images);
            out.set_pixel_at(i, j, col);
        }
    }
}
