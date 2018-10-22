//
// Created by Joona on 21/10/2018.
//
#include "Common.h"
#include "Worlds.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Sphere.h"

namespace Worlds {
    const Hitable *const random_scene(Scene &sc) {
        auto s1_mat = sc.add_material<Lambertian>(vec3(0.5, 0.5, 0.5));
        auto glass = sc.add_material<Dielectric>(1.5);
        auto s3_mat = sc.add_material<Lambertian>(vec3(0.4, 0.2, 0.1));
        auto s4_mat = sc.add_material<Metal>(vec3(0.7, 0.6, 0.5), 0.0);

        sc.add_hitable<Sphere>(vec3(0, -1000, 0), 1000, s1_mat);
        sc.add_hitable<Sphere>(vec3(0, 1, 0), 1.0, glass);
        sc.add_hitable<Sphere>(vec3(-4, 1, 0), 1.0, s3_mat);
        sc.add_hitable<Sphere>(vec3(4, 1, 0), 1.0, s4_mat);

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                const Float choose_mat = rng::get();
                const vec3 center(a + 0.9 * rng::get(), 0.2, b + 0.9 * rng::get());
                if ((center - vec3(4, 0.2, 0)).len() > 0.9) {
                    if (choose_mat < 0.8) {
                        auto diffuse = sc.add_material<Lambertian>(vec3(rng::get() * rng::get(),
                                                                           rng::get() * rng::get(),
                                                                           rng::get() * rng::get()));
                        sc.add_hitable<Sphere>(center, 0.2, diffuse);
                    } else if (choose_mat < 0.95) {
                        auto metal = sc.add_material<Metal>(vec3(0.5 * (1 + rng::get()),
                                                                    0.5 * (1 + rng::get()), 0.5 * (1 + rng::get())),
                                                               0.5 * rng::get());
                        sc.add_hitable<Sphere>(center, 0.2, metal);
                    } else {
                        sc.add_hitable<Sphere>(center, 0.2, glass);
                    }
                }
            }
        }
        return sc.make_hitable_list();
    }

    const Hitable *const example_world(Scene &sc) {
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

    const Hitable *const animation(Scene &sc, Float t) {
        Float R = 10;
        Float r = 2;
        auto diffuse = sc.add_material<Lambertian>(vec3(0.1, 0.2, 0.5));
        auto glass = sc.add_material<Dielectric>(2.0);
        auto metal = sc.add_material<Metal>(vec3(0.8, 0.6, 0.2), 0.3);
        vec3 center{0, 0, 0};
        vec3 center2{R * cos(2 * pi * t), 0, R * sin(2 * pi * t)};
        vec3 center3 = center2 + vec3(r * cos(2 * pi * t * 2), 0, r * sin(2 * pi * t * 2));
        sc.add_hitable<Sphere>(center, 3.5, metal);
        sc.add_hitable<Sphere>(center2, 1, glass);
        sc.add_hitable<Sphere>(center3, 0.5, diffuse);
        return sc.make_hitable_list();
    }

    const Hitable *const atom_animation(Scene &sc, Float t) {
        //auto e_mat = sc.add_material<Metal>(vec3(0.1, 0.2, 0.5), 0.1);
        //auto p_mat = sc.add_material<Metal>(vec3(1, 0.2, 0.2), 0.3);
        //auto n_mat = sc.add_material<Metal>(vec3(0.2, 0.2, 0.2), 0.3);
        auto e_mat = sc.add_material<Lambertian>(vec3(0.1, 0.2, 0.6));
        auto glass = sc.add_material<Dielectric>(1.5);
        auto p_mat = glass;
        auto n_mat = glass;
        vec3 dr1{cos(2 * pi * t), sin(2 * pi * t), -1.0 / 3};
        vec3 dr2{cos(2 * pi * t + 2 * pi / 3), sin(2 * pi * t + 2 * pi / 3), -1.0 / 3};
        vec3 dr3{cos(2 * pi * t + 4 * pi / 3), sin(2 * pi * t + 4 * pi / 3), -1.0 / 3};
        vec3 dr4{0, 0, 1};
        Float r_c = sqrt(8.0 / 9.0);
        vec3 proton1 = r_c * dr1;
        vec3 proton2 = r_c * dr2;
        vec3 neutron1 = r_c * dr3;
        vec3 neutron2 = dr4;
        Float r_e = 10;
        vec3 center2{r_e * cos(2 * pi * t), 0, r_e * sin(2 * pi * t)};
        vec3 center3{r_e * cos(2 * pi * (t - 0.5)), r_e * sin(2 * pi * (t - 0.5)), 0};
        sc.add_hitable<Sphere>(proton1, 2, p_mat);
        sc.add_hitable<Sphere>(proton2, 2, p_mat);
        sc.add_hitable<Sphere>(neutron1, 2, n_mat);
        sc.add_hitable<Sphere>(neutron2, 2, n_mat);
        sc.add_hitable<Sphere>(center2, 1, e_mat);
        sc.add_hitable<Sphere>(center3, 1, e_mat);
        return sc.make_hitable_list();
    }
}
