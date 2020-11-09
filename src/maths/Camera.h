#pragma once
#include <maths/Vec3.h>
#include <maths/Ray.h>


class Camera{

    private:
        Point3 _origin;
        Point3 _lowerLeftCorner;
        Vec3 _horizontal;
        Vec3 _vertical;
        Vec3 _u, _v, _w;
        double _lensRadius;
        double _time0, _time1; 
    public:
        Camera(Point3 lookFrom, Point3 lookAt, Vec3 verticalUp, double verticalFOV, double aspectRatio, double aperture, double focus_dist, double _time0 = 0, double _time1 = 0);
        Ray getRay(double u, double v);


};