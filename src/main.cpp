#include <iostream>
#include <random>

#include "raytracer/common.h"
#include "raytracer/Image.h"
#include "raytracer/Ray.h"
#include "raytracer/Sphere.h"
#include "raytracer/Hitable.h"
#include "raytracer/HitableList.h"
#include "raytracer/Camera.h"
#include "raytracer/UnitRandomGenerator.h"
#include "raytracer/Material.h"
#include "raytracer/Lambertian.h"
#include "raytracer/Metal.h"
#include "raytracer/Dielectric.h"


vec3 color(const Ray& r, const Hitable* const world, int depth) {
    HitRecord rec;
    Interval interval {0.001, 1e10};
    if (world->hit(r, interval, rec)) {
        Ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
           return attenuation * color(scattered, world, depth+1);
        }
        else {
            return vec3(0, 0, 0);
        }
    }
    else {
        Float t_miss = 0.5 * (r.unit_direction().y + 1.0);
        return (1.0 - t_miss)*vec3(1.0, 1.0, 1.0) + t_miss*vec3(0.5, 0.7, 1.0);
    }
}


int main() {
    constexpr int width = 600;
    constexpr int height = 300;
    constexpr int num_samples = 400;
    Image im = {width, height};
    Lambertian s1_material {vec3(0.1, 0.2, 0.5)};
    Lambertian s2_material {vec3(0.8, 0.8, 0.0)};
    Metal s3_material {vec3(0.8, 0.6, 0.2), 0.3};
    Dielectric s4_material {1.5};
    Dielectric s5_material {1.5};
    Sphere s1 = {{0, 0, -1}, 0.5, &s1_material};
    Sphere s2 = {{0, -100.5, -1}, 100, &s2_material};
    Sphere s3 = {{1, 0, -1}, 0.5, &s3_material};
    Sphere s4 = {{-1, 0, -1}, 0.5, &s4_material};
    Sphere s5 = {{-1, 0, -1}, -0.45, &s5_material};
    HitableList list;
    list.add(&s1);
    list.add(&s2);
    list.add(&s3);
    list.add(&s4);
    list.add(&s5);
    Hitable* world = &list;
    Camera cam;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            vec3 col = {0, 0, 0};
            for (int s=0; s < num_samples; s++) {
                Float u_random_bias = rng.get_number();
                Float v_random_bias = rng.get_number();
                const Float u = (i + u_random_bias) / Float(width);
                const Float v = (j + v_random_bias) / Float(height);
                Ray r = cam.get_ray(u, -v);
                col += color(r, world, 0);
            }
            col /= Float(num_samples);
            col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
            im.set_pixel_at(i, j, col);
        }
    }
    im.to_ppm("test.ppm");
    return 0;
}