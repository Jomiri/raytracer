#include <iostream>
#include "../include/raytracer/vector3d.h"
#include "../include/raytracer/Image.h"

int main() {
    constexpr int width = 200;
    constexpr int height = 100;

    Image im = {width, height};

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            const double r = double(i) / double(width);
            const double g = double(height-j) / double(height);
            const double b = 0.2;
            const vec3 pixel = vec3{r, g, b};
            im.set_pixel_at(i, j, pixel);
        }
    }

    im.to_ppm("test.ppm");


    return 0;
}