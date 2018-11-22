//
// Created by fd on 20.11.2018.
//

#ifndef PBR_TRIANGLE_H
#define PBR_TRIANGLE_H


#include <glm/vec3.hpp>
#include "../core/ray.h"
#include "../core/shape.h"

class Triangle: public Shape {
private:
    glm::vec3 v0, v1, v2;

public:
    Triangle(glm::vec3 v0,glm::vec3 v1,glm::vec3 v2, glm::vec3 color);
    double intersect(const Ray &r) const override;
};


#endif //PBR_TRIANGLE_H
