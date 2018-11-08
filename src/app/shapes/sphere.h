//
// Created by fd on 04.11.2018.
//

#ifndef ASSIGNMENT1_SPHERE_H
#define ASSIGNMENT1_SPHERE_H

#include "glm/glm.hpp"
#include "../core/ray.h"

class Sphere {
public:
    double rad;    // radius
    glm::vec3 p, c;      // position, color

    Sphere(double rad_, glm::vec3 p_, glm::vec3 c_)
            : rad(rad_), p(p_), c(c_){};

    double intersect(const Ray &r) const;
};

#endif //ASSIGNMENT1_SPHERE_H
