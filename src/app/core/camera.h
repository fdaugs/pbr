//
// Created by fd on 10.11.2018.
//

#ifndef PBR_CAMERA_H
#define PBR_CAMERA_H

#include "glm/glm.hpp"
#include "ray.h"

class Camera {
protected:
    double fovx;
    int width ;
    int height;
    double fovy;
    glm::vec3 position;
    glm::vec3 lookat;
    glm::vec3 up;
public:
    Camera(glm::vec3 position, glm::vec3 upvector, glm::vec3 lookat, double fov, int width, int height);
    virtual Ray generateRay(int x, int y)=0;
    glm::mat3 camToWorld();
};


#endif //PBR_CAMERA_H
