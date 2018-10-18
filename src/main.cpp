#include <iostream>
#include <random>
#include <memory>

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

class Scene {
    using Mat = std::unique_ptr<Material>;
    using Obj = std::unique_ptr<Hitable>;
public:
    Hitable* example_world() {
        Mat s1_material = std::make_unique<Lambertian>(vec3(0.1, 0.2, 0.5));
        Mat s2_material = std::make_unique<Lambertian>(vec3(0.8, 0.8, 0.0));
        Mat s3_material = std::make_unique<Metal>(vec3(0.8, 0.6, 0.2), 0.3);
        Mat s4_material = std::make_unique<Dielectric>(1.5);

        Obj s1 = std::make_unique<Sphere>(vec3{0, 0, -1}, 0.5, s1_material.get());
        Obj s2 = std::make_unique<Sphere>(vec3{0, -100.5, -1}, 100, s2_material.get());
        Obj s3 = std::make_unique<Sphere>(vec3{1, 0, -1}, 0.5, s3_material.get());
        Obj s4 = std::make_unique<Sphere>(vec3{-1, 0, -1}, 0.5, s4_material.get());
        Obj s5 = std::make_unique<Sphere>(vec3{-1, 0, -1}, 0.45, s4_material.get());

        list.add(s1.get());
        list.add(s2.get());
        list.add(s3.get());
        list.add(s4.get());
        list.add(s5.get());

        materials.push_back(std::move(s1_material));
        materials.push_back(std::move(s2_material));
        materials.push_back(std::move(s3_material));
        materials.push_back(std::move(s4_material));

        objects.push_back(std::move(s1));
        objects.push_back(std::move(s2));
        objects.push_back(std::move(s3));
        objects.push_back(std::move(s4));
        objects.push_back(std::move(s5));

        return &list;
    }
    std::vector<std::unique_ptr<Material>> materials;
    std::vector<std::unique_ptr<Hitable>> objects;
    HitableList list;
};


int main() {
    constexpr int factor = 2;
    constexpr int width = factor * 200;
    constexpr int height = factor * 100;
    constexpr int num_samples = 200;
    Image im = {width, height};
    Scene scene;
    auto world = scene.example_world();
    vec3 lookfrom(3,3,2);
    vec3 lookat(0,0,-1);
    Float focal_length = (lookfrom - lookat).len();
    Float aperture = 2.0;
    Camera cam(lookfrom, lookat, vec3(0,1,0), 20, Float(width)/Float(height), aperture, focal_length);
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