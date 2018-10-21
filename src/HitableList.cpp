//
// Created by Joona on 14/10/2018.
//

#include "Common.h"
#include "HitableList.h"

bool HitableList::hit(const Ray& r, const Interval& t_limits, HitRecord& rec) const {
    HitRecord temp_rec {rec};
    Interval temp_limits {t_limits};
    for (const auto& h: list) {
        if (h->hit(r, temp_limits, temp_rec)) {
            temp_limits.max = temp_rec.t;
            rec = temp_rec;
        }
    }
    return temp_limits.max < t_limits.max;
}

void HitableList::add(Hitable* h) {
    list.push_back(h);
}

void HitableList::reset() {
    list.clear();
}

