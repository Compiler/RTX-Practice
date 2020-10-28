#pragma once
#include <maths/Vec3.h>
#include <maths/Ray.h>
struct HitRecord{
    Point3 point;
    Vec3 normal;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal){
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }

};

class Hittable{

    public:
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const = 0;

};