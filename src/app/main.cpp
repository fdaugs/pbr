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
#include "core/ray.h"
#include "shapes/sphere.h"
#include "core/image.h"
#include "core/Scene.h"
#include <memory>



inline double clamp(double x){
    return x<0 ? 0 : x>1 ? 1 : x;
}

inline int toInt(double x){
    return static_cast<int>(lround(pow(clamp(x),1/2.2)*255));
}

glm::vec3 radiance(const Ray &r, const Scene &scene){
    double t;                               // distance to intersection

    auto object = scene.intersect(r, t);

    if(object == nullptr){
        return glm::vec3(); // if miss, return black
    }
    return object->c;

}

int main(int argc, char *argv[]){

    try {

        Scene myScene;
        myScene.loadScene();


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

                r = radiance(Ray(cam.o, glm::normalize(d)), myScene);
                c[i] = c[i] + glm::vec3(clamp(r.x), clamp(r.y), clamp(r.z));
            }
        }
        cv::Mat M(w,h, CV_8UC3, cv::Scalar(0,0,255));

        auto out = std::make_unique<Image>(w, h);
        //memcpy(out->img.data, c.data(), c.size());
        out->img = M;
        out->show("Test");

        FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
        fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
        for (int i=0; i<w*h; i++){
            std::cout << c[i].y << std::endl;
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