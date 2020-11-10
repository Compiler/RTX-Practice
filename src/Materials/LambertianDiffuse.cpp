#include "LambertianDiffuse.h"
LambertianDiffuse::LambertianDiffuse():_albedo(Point3(1,1,1)){}


LambertianDiffuse::LambertianDiffuse(const Color& a): _albedo(a){


}

bool LambertianDiffuse::scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const{
    Vec3 scatterDirection = record.normal + random_unit_vector();
   
    //if(scatteredDirection.near_zero())scatteredDirection = record.normal;
    
    scatteredRay = Ray(record.point, scatterDirection, rayIn.time);
    attenuation = _albedo;
    return true;

}