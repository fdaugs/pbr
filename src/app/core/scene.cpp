//
// Created by fd on 08.11.2018.
//

#include "scene.h"
#include "../shapes/triangle.h"
#include "glm/glm.hpp"
#include <memory>

void Scene::loadScene() {
    // colors
    auto red = glm::vec3(255,0,0);
    auto blue = glm::vec3(0,0,255);
    auto gray = glm::vec3(0.75,0.75,.75);
    auto white = glm::vec3(1,1,1);

    //Objects
    objects.push_back(std::make_shared<Sphere>(16.5,glm::vec3(27,16.5,47),       glm::vec3(0,255,0)));//Mirr
    objects.push_back(std::make_shared<Sphere>(16.5,glm::vec3(73,16.5,78),       glm::vec3(255,255,0)));//Glas
    objects.push_back(std::make_shared<Triangle>(glm::vec3(27,16.5,80), glm::vec3(73,16.5,80), glm::vec3(50,50,80), glm::vec3(0,0,255)));

    //Box
    //Right
    objects.push_back(std::make_shared<Triangle>(glm::vec3(100,0,0), glm::vec3(100,0,200), glm::vec3(100,80,0), glm::vec3(0,0,255)));
    objects.push_back(std::make_shared<Triangle>(glm::vec3(100,80,200), glm::vec3(100,0,200), glm::vec3(100,80,0), glm::vec3(0,0,255)));

    //Left
    objects.push_back(std::make_shared<Triangle>(glm::vec3(0,0,0), glm::vec3(0,0,200), glm::vec3(0,80,0), glm::vec3(255,0,0)));
    objects.push_back(std::make_shared<Triangle>(glm::vec3(0,80,200), glm::vec3(0,0,200), glm::vec3(0,80,0), glm::vec3(255,0,0)));

    //Bottom
    objects.push_back(std::make_shared<Triangle>(glm::vec3(0,0,0), glm::vec3(100,0,0), glm::vec3(0,0,200), gray));
    objects.push_back(std::make_shared<Triangle>(glm::vec3(100,0,200), glm::vec3(100,0,0), glm::vec3(0,0,200), gray));

    //Back
    objects.push_back(std::make_shared<Triangle>(glm::vec3(0,0,0), glm::vec3(0,80,0), glm::vec3(100,0,0), gray));
    objects.push_back(std::make_shared<Triangle>(glm::vec3(100,80,0), glm::vec3(0,80,0), glm::vec3(100,0,0), gray));

    //Top
    objects.push_back(std::make_shared<Triangle>(glm::vec3(0,80,0), glm::vec3(0,80,200), glm::vec3(100,80,200), gray));
    objects.push_back(std::make_shared<Triangle>(glm::vec3(0,80,0), glm::vec3(100,80,0), glm::vec3(100,80,200), gray));

    //Light
    objects.push_back(std::make_shared<Triangle>(glm::vec3(25,75,100), glm::vec3(25,75,150), glm::vec3(75,75,150), white));
    objects.push_back(std::make_shared<Triangle>(glm::vec3(25,75,100), glm::vec3(75,75,100), glm::vec3(75,75,150), white));

}

std::shared_ptr<Shape> Scene::intersect(const Ray &r, double &t) const {
    double d;
    t = DBL_MAX;
    std::shared_ptr<Shape> object = nullptr;

    for(auto i=0; i<objects.size(); ++i)
    {
        if((d=objects[i]->intersect(r)) && (d<t))
        {
            t=d;
            object = objects[i];
        }
    }

    return object;
}