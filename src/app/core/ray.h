//
// Created by fd on 04.11.2018.
//

#ifndef PBR_RAY_H
#define PBR_RAY_H

#include "glm/glm.hpp"

/**
 * A class representing a Ray.
 */
struct Ray {
    glm::vec3 o; // Origin
    glm::vec3 d; // Distance

    /**
     * Create a Ray.
     * @param o_ origin
     * @param d_ distance
     */
    Ray(glm::vec3 o_, glm::vec3 d_)
            : o(o_), d(d_) {}
};


#endif //PBR_RAY_H