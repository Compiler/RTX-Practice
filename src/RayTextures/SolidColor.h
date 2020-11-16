#pragma once 
#include <RayTextures/Texture.h>


class SolidColor : public Texture{

    private:
        Color _colorValue;
    public:
        SolidColor();
        SolidColor(Color color);
        SolidColor(double r, double g, double b);

        virtual Color value(double u, double v, const Point3& point) const override;


};