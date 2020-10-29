#pragma once

#include <Materials/Material.h>

class LambertianDiffuse : public Material{
    private:
        Color _albedo;
    public:
        LambertianDiffuse();
        LambertianDiffuse(const Color& a);
        virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override;


};