#include <sstream>

#include "Common.h"
#include "Image.h"
#include "Ray.h"
#include "Hitable.h"
#include "Camera.h"
#include "Random.h"
#include "Scene.h"
#include "Worlds.h"
#include "Render.h"


int main() {
    constexpr int factor {4};
    constexpr int width {factor * 100};
    constexpr int height {factor * 100};
    constexpr int num_samples {200};
    constexpr int num_frames {1};
    const vec3 lookfrom {30, 0, 0};
    const vec3 lookat {0, 0, 0};
    const vec3 vup {0, 1, 1};
    const Float fov {36};
    const Float aspect = Float(width)/Float(height);
    const Float aperture = 0.001;
    const Float focal_length = 10;
    const Camera cam(lookfrom, lookat, vup, fov, aspect, aperture, focal_length);
    for (int i = 0; i < num_frames; i++) {
        Image im {width, height};
        Scene scene;
        auto world = Worlds::atom_animation(scene, Float(i)/num_frames);
        async_render(world, cam, num_samples, im);
        im.gamma_correct();
        std::stringstream sst;
        sst << "anim/a" << i << ".png";
        im.to_png(sst.str());
    }
    return 0;
}