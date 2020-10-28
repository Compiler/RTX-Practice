#pragma once
#include <maths/Vec3.h>
#include <maths/Ray.h>


class Camera{

    private:
        Point3 _origin;
        Point3 _lowerLeftCorner;
        Vec3 _horizontal;
        Vec3 _vertical;
    public:
        Camera();
        Ray getRay(double u, double v);


};