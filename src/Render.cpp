//
// Created by Joona on 21/10/2018.
//

#include <thread>
#include <future>

#include "Render.h"
#include "Common.h"
#include "Hitable.h"
#include "Camera.h"
#include "Image.h"
#include "Material.h"

vec3 ambient_color(const Ray& r) {
    //Float t_miss = 0.5 * (r.unit_direction().y + 1.0);
    //return (1.0 - t_miss)*vec3(1.0, 1.0, 1.0) + t_miss*vec3(0.5, 0.7, 1.0);
    return {1, 1, 1};
}

vec3 color(const Ray& r, const Hitable* const world, int depth) {
    const Interval interval {0.001, std::numeric_limits<Float>::max()};
    HitRecord rec;
    if (world->hit(r, interval, rec)) {
        Ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * color(scattered, world, depth+1);
        else
            return vec3(0, 0, 0);
    }
    else
        return ambient_color(r);
}

void render(const Hitable *const world, const Camera& cam, int num_samples, Image& im) {
    const int width = im.get_width();
    const int height = im.get_height();
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            vec3 col {0, 0, 0};
            for (int s = 0; s < num_samples; s++) {
                const Float u_random_bias = rng::get();
                const Float v_random_bias = rng::get();
                const Float u = (i + u_random_bias) / Float(width);
                const Float v = (j + v_random_bias) / Float(height);
                const Ray r = cam.get_ray(u, -v);
                col += color(r, world, 0);
            }
            col /= Float(num_samples);
            im.set_pixel_at(i, j, col);
        }
        if ((j+1)%progress_print_interval == 0)
            std::cout << "Finished rendering row: " << j+1 << std::endl;
    }
}

void async_render(const Hitable *const world, const Camera& cam, int num_samples, Image& out) {
    // num_samples is treated as a suggestion
    const int suggested_threads = std::max<int>(std::thread::hardware_concurrency(), 1);
    const int num_threads = std::min<int>(suggested_threads, num_samples);
    const int samples_per_thread = std::max<int>(num_samples / num_threads, 1);
    std::vector<Image> images;
    images.reserve(num_threads); //Reserve memory here to avoid reallocation in the loop
    std::vector<std::future<void>> futures;
    for (int i = 0; i < num_threads; i++) {
        images.emplace_back(out.get_width(), out.get_height());
        futures.push_back(std::async(std::launch::async, render, world, std::ref(cam),
                                     samples_per_thread, std::ref(images.at(i))));
    }
    for (auto &f : futures) {
        f.get();
    }
    average_images(images, out);
}