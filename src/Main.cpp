#include <sstream>

#include "Common.h"
#include "Image.h"
#include "Hitable.h"
#include "Camera.h"
#include "Scene.h"
#include "Worlds.h"
#include "Render.h"


int main() {
    constexpr int factor {4};
    constexpr int width {factor * 100};
    constexpr int height {factor * 100};
    constexpr int num_samples {1000};
    constexpr int num_frames {1};
    const vec3 look_from {30, 0, 0};
    const vec3 look_at {0, 0, 0};
    const vec3 view_up {0, 1, 1};
    const Float vertical_fov {36};
    const Float aspect = Float(width)/Float(height);
    const Float aperture = 0.001;
    const Float focal_length = 10;
    const Camera cam(look_from, look_at, view_up, vertical_fov, aspect, aperture, focal_length);
    for (int i = 0; i < num_frames; i++) {
        Image im {width, height};
        Scene scene;
        Float t = Float(i) / num_frames;
        auto world = Worlds::atom_animation(scene, t);
        async_render(world, cam, num_samples, im);
        std::stringstream sst;
        sst << "anim/frame" << i << ".png";
        im.gamma_correct();
        im.to_png(sst.str());
    }
    return 0;
}