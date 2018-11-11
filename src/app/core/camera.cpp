//
// Created by fd on 10.11.2018.
//

#include "camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 upvector, glm::vec3 lookatpoint, double fov, int width, int height)
    : position(position), upvector(upvector) , width(width), height(height)
{
    this->lookatpoint = glm::normalize(lookatpoint);
    float ratio = static_cast<double>(height)/width;
    fovx = fov;
    fovy = ratio * fovx;
}

glm::mat3 Camera::camToWorld() {
    {
        using namespace glm;
        vec3 xaxis = normalize(cross(upvector, lookatpoint));
        vec3 yaxis = normalize(cross(lookatpoint, upvector));


        mat3 camToWorld;

        camToWorld[0][0] = xaxis.x;
        camToWorld[0][1] = yaxis.x;
        camToWorld[0][2] = lookatpoint.x;
        camToWorld[1][0] = xaxis.y;
        camToWorld[1][1] = yaxis.y;
        camToWorld[1][2] = lookatpoint.y;
        camToWorld[2][0] = xaxis.z;
        camToWorld[2][1] = yaxis.z;
        camToWorld[2][2] = lookatpoint.z;
    }
}