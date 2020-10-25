#pragma once
#include <iostream>

#include <maths/Vec3.h>
#include <maths/Ray.h>
double RayHitSphere(const Point3& sphereCenter, double sphereRadius, const Ray& r);

void writeColor(std::ostream &out, Color& pixelColor){

    out << (int)(255.999 * pixelColor.x()) << ' ' << (int)(255.999 *  pixelColor.y()) << ' ' << (int)(255.999 *  pixelColor.z()) << '\n';

}

Color RayColor(const Ray& r) {
    double hit = RayHitSphere(Point3(0,0,-1), 0.5, r);
    if (hit > 0.0) {
        Vec3 N = unit_vector(r.at(hit) - Vec3(0,0,-1));
        return 0.5*Color(N.x()+1, N.y()+1, N.z()+1);
    }
    Vec3 unit_direction = unit_vector(r.direction());
    hit = 0.5*(unit_direction.y() + 1.0);
    return (1.0-hit)*Color(1.0, 1.0, 1.0) + hit*Color(0.5, 0.7, 1.0);
}

double RayHitSphere(const Point3& sphereCenter, double sphereRadius, const Ray& r){
    Vec3 RayStart = r.origin();
    Vec3 oc = RayStart - sphereCenter;
    float a = dot(r.direction(), r.direction());
    float halfB=  dot(oc, r.direction());     
    float c = dot(oc, oc) - sphereRadius*sphereRadius;
    float discriminant = halfB * halfB - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-halfB - sqrt(discriminant) ) / a;
    }


}

int main(){

    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;

    double viewportHeight = 2.0;
    double viewportWidth = ASPECT_RATIO * viewportHeight;
    double focalLength = 1.0;

    Point3 origin = Point3(0, 0, 0);
    Vec3 horizontal = Vec3(viewportWidth, 0, 0);
    Vec3 vertical = Vec3(0, viewportHeight, 0);

    Vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++){
            double u = (double(x) / (IMAGE_WIDTH - 1));
            double v = (double(y) / (IMAGE_HEIGHT - 1));
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            Color pixelColor = RayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}