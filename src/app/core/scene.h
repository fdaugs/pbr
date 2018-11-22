//
// Created by fd on 08.11.2018.
//

#ifndef PBR_SCENE_H
#define PBR_SCENE_H


#include <vector>
#include "../shapes/sphere.h"
#include <memory>

class Scene {
    std::vector<std::shared_ptr<Shape>> objects;

public:
    void loadScene();
    std::shared_ptr<Shape> intersect(const Ray &r, double &t) const;
    Scene(){};

};


#endif //PBR_SCENE_H
