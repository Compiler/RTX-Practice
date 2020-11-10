#include "Dialectric.h"


Dialectric::Dialectric(double indexOfRefraction):_ir(indexOfRefraction){}
bool Dialectric::scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const{
    attenuation = Color(1.0, 1.0, 1.0);
    double refraction_ratio = record.frontFace ? (1.0/_ir) : _ir;

    Vec3 unit_direction = unit_vector(rayIn.direction());
    double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;

     if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, record.normal);
    else
        direction = refract(unit_direction, record.normal, refraction_ratio);

    scatteredRay = Ray(record.point, direction, rayIn.time);
    return true;
}


double Dialectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}