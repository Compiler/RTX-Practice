#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <maths/Vec3.h>
#include <maths/Ray.h>
#include <RayHittables/Sphere.h>
double RayHitSphere(const Point3& sphereCenter, double sphereRadius, const Ray& r);

Color RayColor(const Ray& r) {
    //Sphere sphere(Point3(0, 0, -1), 0.5);
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
    Vec3 oc = r.origin() - sphereCenter;
    float a = r.direction().length_squared();
    float halfB=  dot(oc, r.direction());     
    float c = oc.length_squared() - sphereRadius*sphereRadius;
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

    FILE* file;
    file = fopen("image.ppm", "w+");
    fprintf(file, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    for(int y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++){
            double u = (double(x) / (IMAGE_WIDTH - 1));
            double v = (double(y) / (IMAGE_HEIGHT - 1));
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            Color pixelColor = RayColor(r);
            int red = (int)(255.999 * pixelColor.x());
            int green = (int)(255.999 * pixelColor.y());
            int blue = (int)(255.999 * pixelColor.z());
            fprintf(file, "%d %d %d\n", red, green, blue);
        }
    }
    std::cerr << "\nDone.\n";
    fclose(file);
    return 0;
}