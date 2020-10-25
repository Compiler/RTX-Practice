#include "Sphere.h"




Sphere::Sphere(Point3 center, double radius):_center(center), _radius(radius){}
bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const {
    Vec3 oc = r.origin() - _center;
    float a = dot(r.direction(), r.direction());
    float halfB=  dot(oc, r.direction());     
    float c = dot(oc, oc) - _radius*_radius;
    float discriminant = halfB * halfB - a*c;
    if (discriminant > 0){
        double root = sqrt(discriminant);

        double temp = (-halfB - root) / a;
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