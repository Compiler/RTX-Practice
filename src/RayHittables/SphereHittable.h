#pragma once
#include <RayHittables/RayHittableObject.h>

 class SphereHittable : public RayHittableObject{
    private:
        Point3 _center;
        double _radius;
    public:
        SphereHittable(Vec3 position, double radius): _center(position), _radius(radius){}
        virtual bool hit(const Ray& currentRay, double t_min, double t_max, RayHitRecord& hitRecord) const override;


 };