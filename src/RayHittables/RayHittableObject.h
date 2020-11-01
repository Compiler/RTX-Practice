#pragma once
#include <maths/Ray.h>
#include <maths/Vec3.h>

struct RayHitRecord{
    Point3 collisionPoint;
    Vec3 collisionNormal;
    double t;
    bool frontFacingNormal;

    void setNormalFace(const Ray& currentRay, const Vec3& outwardNormal){
        frontFacingNormal = dot(currentRay.dir, outwardNormal) < 0;
        collisionNormal = frontFacingNormal ? outwardNormal : -outwardNormal;

    }


};

class RayHittableObject{
    public:
        virtual bool hit(const Ray& currentRay, double t_min, double t_max, RayHitRecord& hitRecord) const = 0;


};