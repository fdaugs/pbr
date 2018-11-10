//
// Created by fd on 08.11.2018.
//

#ifndef PBR_SCENE_H
#define PBR_SCENE_H


#include <vector>
#include "../shapes/sphere.h"

class Scene {
    std::vector<Sphere> objects;

public:
    void loadScene();
    const Sphere* intersect(const Ray &r, double &t) const;
    Scene(){};

};


#endif //PBR_SCENE_H
