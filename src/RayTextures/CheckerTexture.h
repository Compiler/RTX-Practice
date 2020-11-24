#pragma once
#include <RayTextures/Texture.h>
#include <RayTextures/SolidColor.h>
class CheckerTexture : public Texture{

    private:
        shared_ptr<Texture> _even;
        shared_ptr<Texture> _odd;
    public:
        CheckerTexture();
        CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
        CheckerTexture(Color evenC, Color oddC);

        virtual Color value(double u, double v, const Point3& point) const override;

};