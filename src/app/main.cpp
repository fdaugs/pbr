/*******************************************************************************
 * This implementation is based on smallpt, a Path Tracer by Kevin Beason, 2008
 * Modified by Martin Eisemann, 2018
 ******************************************************************************/


#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <opencv/cv.h>
#include <memory>
#include "glm/glm.hpp"
#include "core/ray.h"
#include "shapes/sphere.h"
#include "core/image.h"
#include "core/Scene.h"
#include "cameras/simplePinholeCamera.h"



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
        SimplePinholeCamera pCam(glm::vec3(50,40,305), glm::vec3(0,1,0),  glm::vec3(0,0,-1), float (M_PI/10), w, h);

        Ray cam(glm::vec3(50,40,305),glm::normalize(glm::vec3(0,0.0,-1))); // cam pos, dir

        glm::vec3 r;

        // Create Matrix with desired image size
        cv::Mat M(h, w, CV_8UC3, cv::Scalar(255,0,0));

        for(int y = 0; y < M.rows; y++) // Loop over image rows
        {
            std::cout << "\rRendering " << 100.*y/(h-1) << "%" << std::flush;
            for(int x = 0; x < M.cols; x++){ // Loop cols
                Ray ray;
                pCam.generateRay(&ray, glm::vec2(x,y));
                r = radiance(ray, myScene);
                M.at<cv::Vec3b>(y,x) = cv::Vec3b(toInt(clamp(r.z)), toInt(clamp(r.y)), toInt(clamp(r.x)));
            }

        }

        cv::flip(M, M, -1);
        cv::flip(M, M, 1);
        auto out = std::make_unique<Image>(w, h);
        out->img = M;
        out->save("Test.png");
        out->show("Test");

        std::cout << "\nFinished\n";
    }
    catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    catch (...){
        std::cerr << "Uncaught exception thrown!\n";
    }
}