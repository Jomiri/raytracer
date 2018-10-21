#include <thread>
#include <future>

#include "raytracer/common.h"
#include "raytracer/Image.h"
#include "raytracer/Ray.h"
#include "raytracer/Sphere.h"
#include "raytracer/Hitable.h"
#include "raytracer/HitableList.h"
#include "raytracer/Camera.h"
#include "raytracer/Random.h"
#include "raytracer/Material.h"
#include "raytracer/Lambertian.h"
#include "raytracer/Metal.h"
#include "raytracer/Dielectric.h"
#include "raytracer/Scene.h"



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

Hitable* random_scene(Scene& scene) {
    auto s1_mat = scene.add_material<Lambertian>(vec3(0.5, 0.5, 0.5));
    auto glass = scene.add_material<Dielectric>(1.5);
    auto s3_mat = scene.add_material<Lambertian>(vec3(0.4, 0.2, 0.1));
    auto s4_mat = scene.add_material<Metal>(vec3(0.7, 0.6, 0.5), 0.0);

    scene.add_hitable<Sphere>(vec3(0, -1000, 0), 1000, s1_mat);
    scene.add_hitable<Sphere>(vec3(0, 1, 0), 1.0, glass);
    scene.add_hitable<Sphere>(vec3(-4, 1, 0), 1.0, s3_mat);
    scene.add_hitable<Sphere>(vec3(4, 1, 0), 1.0, s4_mat);

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            Float choose_mat = rng::get();
            vec3 center(a+0.9* rng::get(), 0.2, b+0.9* rng::get());
            if ((center-vec3(4,0.2, 0)).len() > 0.9) {
                if (choose_mat < 0.8) {
                    auto diffuse = scene.add_material<Lambertian>(vec3(rng::get()* rng::get(),
                                                                       rng::get()* rng::get(), rng::get()* rng::get()));
                    scene.add_hitable<Sphere>(center, 0.2, diffuse);
                }
                else if(choose_mat < 0.95) {
                    auto metal = scene.add_material<Metal>(vec3(0.5*(1 + rng::get()),
                            0.5*(1 + rng::get()), 0.5*(1 + rng::get())), 0.5* rng::get());
                    scene.add_hitable<Sphere>(center, 0.2, metal);
                }
                else {
                   scene.add_hitable<Sphere>(center, 0.2, glass);
                }
            }
        }
    }

    return scene.make_hitable_list();
}

Hitable* example_world(Scene& sc) {

    auto s1_mat = sc.add_material<Lambertian>(vec3(0.1, 0.2, 0.5));
    auto s2_mat = sc.add_material<Lambertian>(vec3(0.8, 0.8, 0.0));
    auto s3_mat = sc.add_material<Metal>(vec3(0.8, 0.6, 0.2), 0.3);
    auto s45_mat = sc.add_material<Dielectric>(1.5);

    sc.add_hitable<Sphere>(vec3(0, 0, -1), 0.5, s1_mat);
    sc.add_hitable<Sphere>(vec3(0, -100.5, -1), 100, s2_mat);
    sc.add_hitable<Sphere>(vec3(1, 0, -1), 0.5, s3_mat);
    sc.add_hitable<Sphere>(vec3(-1, 0, -1), 0.5, s45_mat);
    sc.add_hitable<Sphere>(vec3(-1, 0, -1), 0.5, s45_mat);

    return sc.make_hitable_list();
}

Hitable* animation(Scene& sc, double t) {
    auto s1_mat = sc.add_material<Lambertian>(vec3(0.1, 0.2, 0.5));
    sc.add_hitable<Sphere>(vec3(0, 0, -1*t), 0.5, s1_mat);
    return sc.make_hitable_list();
}


void render(const Hitable *const world, const Camera& cam, const int num_samples, Image& im) {
    int width = im.get_width();
    int height = im.get_height();
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            vec3 col {0, 0, 0};
            for (int s = 0; s < num_samples; s++) {
                Float u_random_bias = rng::get();
                Float v_random_bias = rng::get();
                const Float u = (i + u_random_bias) / Float(width);
                const Float v = (j + v_random_bias) / Float(height);
                Ray r = cam.get_ray(u, -v);
                col += color(r, world, 0);
            }
            col /= Float(num_samples);
            im.set_pixel_at(i, j, col);
        }
        if ((j+1)%10 == 0)
            std::cout << "Finished row: " << j+1 << std::endl;
    }
}

void combine_images(std::vector<Image>& ims, Image& out) {
    int n_images = ims.size();
    int width = out.get_width();
    int height = out.get_height();
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            vec3 col {0, 0, 0};
            for (int k = 0; k < n_images; k++) {
               col += ims[k].get_pixel_at(i, j);
            }
            col /= Float(n_images);
            out.set_pixel_at(i, j, col);
        }
    }

}

void async_render(const Hitable *const world, const Camera& cam, const int num_samples, Image& out) {
    int num_thread = std::thread::hardware_concurrency();
    std::vector<Image> ims;
    ims.reserve(num_thread);
    std::vector<std::future<void>> futures;
    int samples_per_thread = num_samples / num_thread;
    for (int i = 0; i < num_thread; i++) {
        ims.emplace_back(out.get_width(), out.get_height());
        futures.push_back(std::async(std::launch::async, render, world, std::ref(cam),
                samples_per_thread, std::ref(ims.at(i))));
    }
    try {

        for (auto &f : futures) {
            f.get();
        }
    } catch (std::exception &e) {
        std::cerr << e.what();

    }

    combine_images(ims, out);
}

int main() {
    constexpr int factor = 1;
    constexpr int width = factor * 100;
    constexpr int height = factor * 50;
    constexpr int num_samples = 120;
    Image im {width, height};
    Scene scene;
    auto world = random_scene(scene);
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    Float focal_length = 10.0;
    Float aperture = 0.1;
    Camera cam(lookfrom, lookat, vec3(0,1,0), 20, Float(width)/Float(height), aperture, focal_length);
    async_render(world, cam, num_samples, im);
    im.gamma_correct();
    //im.to_ppm("test.ppm");
    im.to_png("test.png");
    return 0;
}