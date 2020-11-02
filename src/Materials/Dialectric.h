#pragma once

#include <maths/Ray.h>
#include <maths/Vec3.h>
#include <Materials/Material.h>

class Dialectric : public Material{

    private:
        double _ir;
        static double reflectance(double cosine, double ref_idx);
        
        
    public:
        Dialectric(double indexOfRefraction);
        virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override;



};