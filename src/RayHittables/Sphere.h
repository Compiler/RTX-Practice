#pragma once
#include <RayHittables/Hittable.h>

class Sphere : public Hittable{
    private:
        Point3 _center;
        double _radius;

    public:
        Sphere(Point3 center, double radius);
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const;


};  