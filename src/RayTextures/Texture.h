#pragma once

#include <maths/Ray.h>
#include <maths/Vec3.h>

class Texture{
    public:
        virtual Color value(double u, double v, const Point3& point) const = 0;

};