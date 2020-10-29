#include "Metal.h"

Metal::Metal():_albedo(Point3(1,1,1)){}
Metal::Metal(const Color& a): _albedo(a){


}

bool Metal::scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const{
    Vec3 reflectedDirection = reflect(unit_vector(rayIn.direction()), record.normal);
    scatteredRay = Ray(record.point, reflectedDirection);
    attenuation = _albedo;
    return (dot(scatteredRay.direction(), record.normal) > 0);

}