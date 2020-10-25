#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Core.h>

#include <RayHittables/Sphere.h>
#include <RayHittables/HittableList.h>



double RayHitSphere(const Point3& sphereCenter, double sphereRadius, const Ray& r);

Color RayColor(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, 0, _INFINITY_, rec)) {
        return 0.5 * (rec.normal + Color(1,1,1));
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
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


    HittableList world;
    world.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point3(0,-100.5,-1), 100));

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
            Color pixelColor = RayColor(r, world);
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