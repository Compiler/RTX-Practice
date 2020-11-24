#include "CheckerTexture.h"



CheckerTexture::CheckerTexture(){
    
}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd):_even(even), _odd(odd){
    
}

CheckerTexture::CheckerTexture(Color evenC, Color oddC): _even(std::make_shared<SolidColor>(evenC)), _odd(std::make_shared<SolidColor>(oddC)){
    
}

Color CheckerTexture::value(double u, double v, const Point3& point) const{
    double sines = sin(10 * point.x()) * sin(10 * point.y()) * sin(10 * point.z());
    if (sines < 0) return _odd->value(u, v, point);
    else return _even->value(u, v, point);
}