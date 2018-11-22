//
// Created by fd on 04.11.2018.
//

#ifndef PBR_SPHERE_H
#define PBR_SPHERE_H

#include "glm/glm.hpp"
#include "../core/ray.h"
#include "../core/shape.h"

/**
 * A class representing a sphere.
 */
class Sphere: public Shape {
public:
    double rad;         // radius
    glm::vec3 p;     // position, color

    /**
     * Create a sphere.
     * @param rad_ Radius of the sphere
     * @param p_ Position of the sphere
     * @param c_ Color of the sphere
     */
    Sphere(double rad_, glm::vec3 p_, glm::vec3 c_)
            : Shape(c_), rad(rad_), p(p_) {};

    /**
     * Calculates an intersection with a ray.
     * @param r Ray
     * @return Distance parameter of the ray
     */
    double intersect(const Ray &r) const override;
};

#endif //PBR_SPHERE_H
