#pragma once

struct HitRecord{
    Point3 point;
    Vec3 normal;
    double t;

};

class hittable{

    public:
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord record) = 0;

};