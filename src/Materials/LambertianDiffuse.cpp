#include "LambertianDiffuse.h"
LambertianDiffuse::LambertianDiffuse():_albedo(std::make_shared<SolidColor>(1,1,1)){}
LambertianDiffuse::LambertianDiffuse(const Color& a): _albedo(std::make_shared<SolidColor>(a)){}
LambertianDiffuse::LambertianDiffuse(std::shared_ptr<Texture> tex):_albedo(tex){}

bool LambertianDiffuse::scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const{
    Vec3 scatterDirection = record.normal + random_unit_vector();
   
    //if(scatterDirection.near_zero())scatterDirection = record.normal;
    
    scatteredRay = Ray(record.point, scatterDirection, rayIn.time);
    attenuation = _albedo->value(record.u, record.v, record.point);
    return true;

}