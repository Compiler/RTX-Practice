#include "SolidColor.h"

SolidColor::SolidColor(){}

SolidColor::SolidColor(Color color): _colorValue(color){}

SolidColor::SolidColor(double r, double g, double b): _colorValue(r,g,b){}


Color SolidColor::value(double u, double v, const Point3& point) const {
    return _colorValue;

}