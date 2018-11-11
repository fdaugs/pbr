//
// Created by fd on 10.11.2018.
//

#include <iostream>
#include "simplePinholeCamera.h"
#include "../core/ray.h"
#include "glm/gtc/matrix_transform.hpp"

SimplePinholeCamera::SimplePinholeCamera(glm::vec3 position, glm::vec3 upvector,  glm::vec3 lookatpoint, double fov, int width, int height)
    :Camera(position, upvector,  lookatpoint, fov, width, height){};

float SimplePinholeCamera::generateRay(Ray *ray, glm::vec2(pImage)) {
    int x = pImage[0];
    int y = pImage[1];
    double x1to1 = (2.0 * x - width) / width; // x is now in the range [-1,1]
    double y1to1 = (2.0 * y - height) / height; // y is now in the range [-1,1]

    glm::vec3 d(x1to1 * tan(fovx),
                y1to1 * tan(fovy),
                -1.0);
    glm::mat3 m(
            0.940f, -0.342f, 0.0f,
            0.342f, 0.940f, 0.0f,
            0.0f, 0.0f, 1.0f
    );
    glm::mat3 tM = glm::mat3(glm::lookAt(
            position,
            position+lookatpoint,
            upvector
    ));
    //glm::vec4 c = m*d;
    ray->o = position;
    //ray->d = glm::normalize(glm::vec3(c.x,c.y,c.z));
    ray->d = normalize(tM*d);

    return 1;
}