//
// Created by fd on 08.11.2018.
//

#include "scene.h"

void Scene::loadScene() {
    objects = {//Scene: radius, position, emission, color, material
            Sphere(1e5, glm::vec3( 1e5+1,40.8,81.6), glm::vec3(255,0,0)),//Left
            Sphere(1e5, glm::vec3(-1e5+99,40.8,81.6),glm::vec3(0,0,255)),//Right
            Sphere(1e5, glm::vec3(50,40.8, 1e5),     glm::vec3(0.75, 0.75, 0.75)),//Back
            //Sphere(1e5, glm::vec3(50,40.8,-1e5+170), glm::vec3()),//Front
            Sphere(1e5, glm::vec3(50, 1e5, 81.6),    glm::vec3(0.75, 0.75, 0.75)),//Bottom
            Sphere(1e5, glm::vec3(50,-1e5+82.6,81.6),glm::vec3(0.75, 0.75, 0.75)),//Top
            Sphere(16.5,glm::vec3(27,16.5,47),       glm::vec3(0,255,0)),//Mirr
            Sphere(16.5,glm::vec3(73,16.5,78),       glm::vec3(255,255,0)),//Glas
            Sphere(600, glm::vec3(50,681.6-.27,81.6),glm::vec3(120,120,120)) //Lite
    };
}

const Sphere* Scene::intersect(const Ray &r, double &t) const {
    double d;
    t = DBL_MAX;
    const Sphere* object = nullptr;

    for(auto i=0; i<objects.size(); ++i)
    {
        if((d=objects[i].intersect(r)) && (d<t))
        {
            t=d;
            object = &(objects[i]);
        }
    }

    return object;
}