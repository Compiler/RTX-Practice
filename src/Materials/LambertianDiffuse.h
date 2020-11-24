#pragma once

#include <Materials/Material.h>
#include <RayTextures/Texture.h>
#include <RayTextures/SolidColor.h>

class LambertianDiffuse : public Material{
    private:
        std::shared_ptr<Texture> _albedo;
    public:
        LambertianDiffuse();
        LambertianDiffuse(const Color& a);
        LambertianDiffuse(std::shared_ptr<Texture> tex);
        virtual bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override;


};