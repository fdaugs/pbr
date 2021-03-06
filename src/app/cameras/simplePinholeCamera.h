//
// Created by fd on 10.11.2018.
//

#ifndef PBR_SIMPLEPINHOLECAMERA_H
#define PBR_SIMPLEPINHOLECAMERA_H

#include "../core/camera.h"

class SimplePinholeCamera: public Camera {
public:
    SimplePinholeCamera(glm::vec3 position, glm::vec3 upvector, glm::vec3 lookatpoint, double fov, int width, int height);
    Ray generateRay(int x, int y) override;
};


#endif //PBR_SIMPLEPINHOLECAMERA_H
