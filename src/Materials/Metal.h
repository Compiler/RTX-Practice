#pragma once
#include <Materials/Material.h>

class Metal : public Material{
    private:
        Color _albedo;
        double _fuzziness;
    public:
        Metal();
        Metal(const Color& a, double fuzziness = 0.0f);
        virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override;


};