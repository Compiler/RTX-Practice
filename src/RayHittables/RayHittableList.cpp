#include "RayHittableList.h"


bool RayHittableList::hit(const Ray& currentRay, double tMin, double tMax, RayHitRecord& hitRecord) const {
    RayHitRecord record;
    bool hitSomething = 0;
    double closest = tMax;

    for(const auto& object : _objects){
        if(object->hit(currentRay, tMin, tMax, record)){
            hitSomething = true;
            closest = record.t;
            hitRecord = record;
        }
    }
    return hitSomething;

}
