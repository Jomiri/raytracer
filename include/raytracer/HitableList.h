//
// Created by Joona on 14/10/2018.
//

#ifndef RAYTRACER_HITABLE_LIST_H
#define RAYTRACER_HITABLE_LIST_H

#include "common.h"
#include "Hitable.h"

class HitableList: public Hitable {
public:
    HitableList() = default;
    bool hit(const Ray& r, const Interval& t_limits, HitRecord& rec) const override;
    void add(Hitable* h);

private:
    std::vector<Hitable*> list;
};

#endif //RAYTRACER_HITABLE_LIST_H
