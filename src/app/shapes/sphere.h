//
// Created by fd on 04.11.2018.
//

#ifndef ASSIGNMENT1_SPHERE_H
#define ASSIGNMENT1_SPHERE_H

#include "glm/glm.hpp"
#include "../core/ray.h"

/**
 * A class representing a sphere.
 */
class Sphere {
public:
    double rad;         // radius
    glm::vec3 p, c;     // position, color

    /**
     * Create a sphere.
     * @param rad_ Radius of the sphere
     * @param p_ Position of the sphere
     * @param c_ Color of the sphere
     */
    Sphere(double rad_, glm::vec3 p_, glm::vec3 c_)
            : rad(rad_), p(p_), c(c_){};

    /**
     * Calculates an intersection with a ray.
     * @param r Ray
     * @return Distance parameter of the ray
     */
    double intersect(const Ray &r) const;
};

#endif //ASSIGNMENT1_SPHERE_H
