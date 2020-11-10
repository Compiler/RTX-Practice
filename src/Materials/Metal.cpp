#include "Metal.h"

Metal::Metal():_albedo(Point3(1,1,1)), _fuzziness(0.0){}
Metal::Metal(const Color& a, double fuzz): _albedo(a), _fuzziness(std::min(fuzz, 1.0)){


}

bool Metal::scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const{
    Vec3 reflectedDirection = reflect(unit_vector(rayIn.direction()), record.normal);
    scatteredRay = Ray(record.point, reflectedDirection + _fuzziness * random_in_unit_sphere(), rayIn.time);
    attenuation = _albedo;
    return (dot(scatteredRay.direction(), record.normal) > 0);

}