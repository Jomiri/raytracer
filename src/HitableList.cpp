//
// Created by Joona on 14/10/2018.
//

#include "raytracer/common.h"
#include "raytracer/HitableList.h"

bool HitableList::hit(const Ray &r, const Interval &t_limits, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    Interval temp_limits = t_limits;
    for (const auto& h: list) {
        if (h->hit(r, temp_limits, temp_rec)) {
            hit_anything = true;
            temp_limits.max = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

void HitableList::add(Hitable* h) {
    list.push_back(h);
}

void HitableList::reset() {
    list.clear();
}

