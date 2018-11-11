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
    glm::vec3 lookatpoint;
    glm::vec3 upvector;
public:
    //Camera() : upvector(glm::vec3(0,1,0)), position(glm::vec3(0,0,0)), lookatpoint(glm::vec3(0,0,-1)), fov(M_PI/10), width(256), height(192), ratio(static_cast<double>(height)/width) {};
    Camera(glm::vec3 position, glm::vec3 upvector, glm::vec3 lookatpoint, double fov, int width, int height);
    virtual ~Camera(){};
    virtual float generateRay(Ray *ray, glm::vec2 pImage)=0;
    glm::mat3 camToWorld();
};


#endif //PBR_CAMERA_H
