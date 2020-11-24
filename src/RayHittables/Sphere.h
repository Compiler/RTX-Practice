#pragma once
#include <memory>
#include <RayHittables/Hittable.h>
#include <Materials/Material.h>

class Sphere : public Hittable{
    private:
        Point3 _center;
        double _radius;
        std::shared_ptr<Material> _material;
        static void getSphereUV(const Point3& point, double& u, double& v);

    public:
        Sphere();
        Sphere(Point3 center, double radius, std::shared_ptr<Material> newMaterial);
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const;


};  