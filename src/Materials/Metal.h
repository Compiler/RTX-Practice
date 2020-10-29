#pragma once
#include <Materials/Material.h>

class Metal : public Material{
    private:
        Color _albedo;
    public:
        Metal();
        Metal(const Color& a);
        virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override;


};