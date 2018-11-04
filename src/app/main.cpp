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

class Vec {        // Usage: time ./smallpt 5000 && xv image.ppm
public:
    double x, y, z;                  // position, also color (r,g,b)

    explicit Vec(double x=0, double y=0, double z=0) {
        this->x=x; this->y=y; this->z=z; }

    Vec operator+(const Vec &rhs) const {
        return Vec(x+rhs.x,y+rhs.y,z+rhs.z); }

    Vec operator-(const Vec &rhs) const {
        return Vec(x-rhs.x,y-rhs.y,z-rhs.z); }

    Vec operator*(double rhs) const {
        return Vec(x*rhs,y*rhs,z*rhs); }

    Vec& norm(){
        return *this = *this * (1/sqrt(x*x+y*y+z*z)); }

    double dot(const Vec &rhs) const {
        return x*rhs.x+y*rhs.y+z*rhs.z; }

    // cross product
    Vec operator%(Vec&rhs){return Vec(y*rhs.z-z*rhs.y,z*rhs.x-x*rhs.z,x*rhs.y-y*rhs.x);}
};

struct Ray {
    Vec o, d;
    Ray(Vec o_, Vec d_)
            : o(o_), d(d_) {}
};

class Sphere {
public:
    double rad;    // radius
    Vec p, c;      // position, color

    Sphere(double rad_, Vec p_, Vec c_)
            : rad(rad_), p(p_), c(c_){}

    double intersect(const Ray &r) const { // returns distance, 0 if nohit
        Vec op = p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        double t;
        double eps = 1e-4;
        double b   = op.dot(r.d);
        double det = b * b - op.dot(op) + rad * rad;
        if (det<0) return 0; else det=sqrt(det);
        return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0);
    }
};

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

Vec radiance(const Ray &r, const std::vector<Sphere>& spheres){
    double t;                               // distance to intersection
    int id=0;                               // id of intersected object

    if (!intersect(r, t, id, spheres)){
        return Vec(); // if miss, return black
    }
    const Sphere &obj = spheres[id];        // the hit object

    return obj.c;

}

int main(int argc, char *argv[]){
    try {
        std::vector<Sphere> spheres = {//Scene: radius, position, emission, color, material
                Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(255,0,0)),//Left
                Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(0,0,255)),//Right
                Sphere(1e5, Vec(50,40.8, 1e5),     Vec(0.75, 0.75, 0.75)),//Back
                //Sphere(1e5, Vec(50,40.8,-1e5+170), Vec()),//Front
                Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(0.75, 0.75, 0.75)),//Bottom
                Sphere(1e5, Vec(50,-1e5+82.6,81.6),Vec(0.75, 0.75, 0.75)),//Top
                Sphere(16.5,Vec(27,16.5,47),       Vec(0,255,0)),//Mirr
                Sphere(16.5,Vec(73,16.5,78),       Vec(255,255,0)),//Glas
                Sphere(600, Vec(50,681.6-.27,81.6),Vec(120,120,120)) //Lite
        };

        int w = 256;
        int h = 192;
        Ray cam(Vec(50,40,305), Vec(0,0.0,-1).norm()); // cam pos, dir

        Vec r;
        std::vector<Vec> c( static_cast<size_t>(w*h) );

        for (int y=0; y<h; y++){ // Loop over image rows
            std::cout << "\rRendering " << 100.*y/(h-1) << "%" << std::flush;

            for (unsigned short x=0; x<w; x++) {   // Loop cols
                int i = (h - y - 1) * w + x; // get pixel index in 1D vector

                double hw    = static_cast<double>(h)/w; // prevent integer division
                double fovx  = M_PI/10;
                double fovy  = hw * fovx;
                double x1to1 = (2.0 * x - w) / w; // x is now in the range [-1,1]
                double y1to1 = (2.0 * y - h) / h; // y is now in the range [-1,1]

                Vec d(x1to1 * tan(fovx),
                      y1to1 * tan(hw * fovx),
                      -1.0);

                r    = radiance(Ray(cam.o, d.norm()), spheres);
                c[i] = c[i] + Vec(clamp(r.x), clamp(r.y), clamp(r.z));
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