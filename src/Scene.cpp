//
// Created by Joona on 21/10/2018.
//

#include "Scene.h"
#include "Hitable.h"

const Hitable *const Scene::make_hitable_list() {
    list.reset();
    for (const auto& h : hitables) {
        list.add(h.get());
    }
    return &list;
}