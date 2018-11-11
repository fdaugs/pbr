//
// Created by fd on 04.11.2018.
//

#include "ray.h"

std::ostream &operator<<(std::ostream &os, const Ray &r) {
    os << "Origin("<<r.o.x<<", "<<r.o.y<<", "<<r.o.z<<"); Direction("<<r.d.x<<", "<<r.d.y<<", "<<r.d.z<<")";
    return os;
}
