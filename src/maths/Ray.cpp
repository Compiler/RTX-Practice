#include "Ray.h"




Ray::Ray(){}


Ray::Ray(const Point3& origin, const Vec3& direction, double tme): orig(origin), dir(direction), time(tme){

}

Point3 Ray::at(double t) const {
    return orig + t*dir;
}