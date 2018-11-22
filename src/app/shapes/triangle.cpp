//
// Created by fd on 20.11.2018.
//

#include <iostream>
#include "triangle.h"
#include "glm/gtx/intersect.hpp"

Triangle::Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 color): v0(v0), v1(v1), v2(v2), Shape(color){}

double Triangle::intersect(const Ray &r) const {
    glm::vec2 pHit;
    float t = 0;
    if(glm::intersectRayTriangle(r.o,r.d,v0,v1,v2, pHit, t)){
        return t;
    }
    return 0;
}