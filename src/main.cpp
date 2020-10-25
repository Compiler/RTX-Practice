#pragma once
#include <iostream>

#include <maths/vec3.h>
#include <maths/ray.h>
bool rayHitSphere(const point3& sphereCenter, double sphereRadius, const ray& r);

void writeColor(std::ostream &out, color& pixelColor){

    out << (int)(255.999 * pixelColor.x()) << ' ' << (int)(255.999 *  pixelColor.y()) << ' ' << (int)(255.999 *  pixelColor.z()) << '\n';

}

color rayColor(const ray& r) {
    if (rayHitSphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

bool rayHitSphere(const point3& sphereCenter, double sphereRadius, const ray& r){
    vec3 rayStart = r.origin();
    vec3 oc = rayStart - sphereCenter;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());     
    float c = dot(oc, oc) - sphereRadius*sphereRadius;
    float discriminant = b*b - 4*a*c;
    return discriminant > 0;


}

int main(){

    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;

    double viewportHeight = 2.0;
    double viewportWidth = ASPECT_RATIO * viewportHeight;
    double focalLength = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal = vec3(viewportWidth, 0, 0);
    vec3 vertical = vec3(0, viewportHeight, 0);

    vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++){
            double u = (double(x) / (IMAGE_WIDTH - 1));
            double v = (double(y) / (IMAGE_HEIGHT - 1));
            ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}