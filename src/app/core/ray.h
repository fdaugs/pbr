//
// Created by fd on 04.11.2018.
//

#ifndef ASSIGNMENT1_CORE_H
#define ASSIGNMENT1_CORE_H

#include "glm/glm.hpp"

struct Ray {
    glm::vec3 o, d;
    Ray(glm::vec3 o_, glm::vec3 d_)
            : o(o_), d(d_) {}
};


#endif //ASSIGNMENT1_CORE_H
