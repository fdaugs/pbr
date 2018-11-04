/*******************************************************************************
 * This implementation is based on smallpt, a Path Tracer by Kevin Beason, 2008
 * Modified by Martin Eisemann, 2018
 ******************************************************************************/


#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <opencv/cv.h>
#include "glm/glm.hpp"
#include "core/core.h"
#include "shapes/sphere.h"




inline double clamp(double x){
    return x<0 ? 0 : x>1 ? 1 : x;
}

inline int toInt(double x){
    return static_cast<int>(lround(pow(clamp(x),1/2.2)*255));
}

inline bool intersect(const Ray &r, double &t, int &id, const std::vector<Sphere>& spheres){
    double d;
    double inf = 1e20;
    t   = 1e20;

    for(auto i=0; i<spheres.size(); ++i)
    {
        if((d=spheres[i].intersect(r)) && (d<t))
        {
            t=d;
            id=i;
        }
    }
    return t<inf;
}

glm::vec3 radiance(const Ray &r, const std::vector<Sphere>& spheres){
    double t;                               // distance to intersection
    int id=0;                               // id of intersected object

    if (!intersect(r, t, id, spheres)){
        return glm::vec3(); // if miss, return black
    }
    const Sphere &obj = spheres[id];        // the hit object

    return obj.c;

}

int main(int argc, char *argv[]){
    try {
        std::vector<Sphere> spheres = {//Scene: radius, position, emission, color, material
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

        int w = 256;
        int h = 192;
        Ray cam(glm::vec3(50,40,305),glm::normalize(glm::vec3(0,0.0,-1))); // cam pos, dir

        glm::vec3 r;
        std::vector<glm::vec3> c( static_cast<size_t>(w*h) );

        for (int y=0; y<h; y++){ // Loop over image rows
            std::cout << "\rRendering " << 100.*y/(h-1) << "%" << std::flush;

            for (unsigned short x=0; x<w; x++) {   // Loop cols
                int i = (h - y - 1) * w + x; // get pixel index in 1D vector

                double hw    = static_cast<double>(h)/w; // prevent integer division
                double fovx  = M_PI/10;
                double fovy  = hw * fovx;
                double x1to1 = (2.0 * x - w) / w; // x is now in the range [-1,1]
                double y1to1 = (2.0 * y - h) / h; // y is now in the range [-1,1]

                glm::vec3 d(x1to1 * tan(fovx),
                      y1to1 * tan(hw * fovx),
                      -1.0);

                r = radiance(Ray(cam.o, glm::normalize(d)), spheres);
                c[i] = c[i] + glm::vec3(clamp(r.x), clamp(r.y), clamp(r.z));
            }
        }



        FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
        fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
        for (int i=0; i<w*h; i++){
            fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
        }

        std::cout << "\nFinished\n";
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    catch (...){
        std::cerr << "Uncaught exception thrown!\n";
    }
}