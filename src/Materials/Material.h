#pragma once
#include <maths/Ray.h>
#include <maths/Vec3.h>
#include <maths/Ray.h>


class Material{

    public:
        virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay);

};