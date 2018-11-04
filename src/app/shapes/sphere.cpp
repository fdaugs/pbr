//
// Created by fd on 04.11.2018.
//

#include "sphere.h"

double Sphere::intersect(const Ray &r) const { // returns distance, 0 if nohit
    glm::vec3 op = p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    double t;
    double eps = 1e-4;
    double b  = glm::dot(op, r.d);
    double det = b * b - glm::dot(op, op) + rad * rad;
    if (det<0) return 0; else det=sqrt(det);
    return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0);
}