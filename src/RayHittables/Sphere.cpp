#include "Sphere.h"



Sphere::Sphere(){

}

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> newMaterial):_center(center), _radius(radius), _material(newMaterial){
    
}

bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const {
    Vec3 oc = r.origin() - _center;
    float a = dot(r.direction(), r.direction());
    float halfB=  dot(oc, r.direction());     
    float c = dot(oc, oc) - _radius*_radius;
    float discriminant = halfB * halfB - a*c;
    if (discriminant > 0){
        double root = sqrt(discriminant);

        double temp = (-halfB - root) / a;
        record.mat_ptr = _material;
        if(temp < tMax && temp > tMin){
            record.t = temp;
            record.point = r.at(record.t);
            record.normal = (record.point - _center) / _radius;
            record.setFaceNormal(r, (record.point - _center) / _radius);
            return true;
        }

        temp = (-halfB + root) / a;
        if(temp < tMax && temp > tMin){
            record.t = temp;
            record.point = r.at(record.t);
            record.normal = (record.point - _center) / _radius;
            record.setFaceNormal(r, (record.point - _center) / _radius);
            return true;
        }

    }

    return false;
}

bool Sphere::boundingBox(double time0, double time1, AABB& outputBox) const{
    outputBox = AABB(_center - Vec3(_radius), _center+Vec3(_radius));
    return true;
}
