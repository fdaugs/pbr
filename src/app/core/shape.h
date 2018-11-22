//
// Created by fd on 20.11.2018.
//

#ifndef PBR_SHAPE_H
#define PBR_SHAPE_H


#include <glm/vec3.hpp>
#include "ray.h"

class Shape {
public:
    glm::vec3 color;

    Shape(glm::vec3 color): color(color){};
    virtual double intersect(const Ray &r) const=0;
};


#endif //PBR_SHAPE_H
