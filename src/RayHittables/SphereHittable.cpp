#include "SphereHittable.h"


bool SphereHittable::hit(const Ray& currentRay, double tMin, double tMax, RayHitRecord& hitRecord) const {
    float t = dot(_center - currentRay.origin(), currentRay.direction());
    Point3 p = currentRay.at(t);
    double y = (_center-p).length();
    if(y > _radius) return false;

    double x = sqrt(_radius * _radius - y*y);
    double t1 = t - x;
    if(t1 > tMin && t1 < tMax){
        hitRecord.collisionPoint = currentRay.at(t1);
        hitRecord.t = t;
        hitRecord.setNormalFace(currentRay, unit_vector(hitRecord.collisionPoint - _center));
        return true;
    }

    double t2 = t - x;
    if(t2 > tMin && t2 < tMax){
        hitRecord.collisionPoint = currentRay.at(t2);
        hitRecord.t = t;
        hitRecord.setNormalFace(currentRay, unit_vector(hitRecord.collisionPoint - _center));
        return true;
    }
    return false;

}
