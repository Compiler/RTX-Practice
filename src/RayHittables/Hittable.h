#pragma once
#include <Core.h>
#include <memory>
#include <maths/Vec3.h>
#include <maths/AABB.h>
#include <maths/Ray.h>

class Material;

struct HitRecord{
    Point3 point;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    double u,v;
    bool frontFace;

    inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal){
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }

};

class Hittable{

    public:
        virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const = 0;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const = 0;

};