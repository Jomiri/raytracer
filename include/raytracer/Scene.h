//
// Created by Joona on 20/10/2018.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "common.h"
#include "Material.h"
#include "Hitable.h"
#include "HitableList.h"


class Scene {
public:
    template <typename MaterialType, typename... Args>
    Material* add_material(Args... material_params) {
        materials.push_back(std::make_unique<MaterialType>(std::forward<Args>(material_params)...));
        return materials.back().get();
    }

    template <typename HitableType, typename... Args>
    Hitable* add_hitable(Args... hitable_params) {
        hitables.push_back(std::make_unique<HitableType>(std::forward<Args>(hitable_params)...));
        return hitables.back().get();
    }

    Hitable* make_hitable_list() {
        list.reset();
        for (const auto& h : hitables) {
            list.add(h.get());
        }
        return &list;
    }

    HitableList list;

private:
    std::vector<std::unique_ptr<Material>> materials;
    std::vector<std::unique_ptr<Hitable>> hitables;
};

#endif //RAYTRACER_SCENE_H
