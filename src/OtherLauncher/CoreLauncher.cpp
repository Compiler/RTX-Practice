#include "CoreLauncher.h"


double hitSphere(const Ray& currentRay, const Point3& sphereCenter, double sphereRadius){
    float t = dot(sphereCenter - currentRay.origin(), currentRay.direction());
    Point3 p = currentRay.at(t);
    double y = (sphereCenter-p).length();
    //std::cout << currentRay.direction().x() << ", " << currentRay.direction().y() << ", " << currentRay.direction().z() << "\n";
    //std::cout << y << " - " << sphereRadius << "\n";
    if(y > sphereRadius) return 0;
    double x = sqrt(sphereRadius * sphereRadius - y*y);
    double t1 = t - x;
    double t2 = t + x;
    return t2;

}


Color getRayColor(const Ray& currentRay, const RayHittableList& world, int depth = 50){
    if (depth <= 0)
        return Color(0,0,0);
    RayHitRecord record;
    if(world.hit(currentRay, 0.001, INFINITY, record)){
        Point3 newTarget = record.collisionPoint + record.collisionNormal + random_in_unit_sphere();
        Ray newRay(record.collisionPoint, newTarget - record.collisionPoint);
        return 0.5 * getRayColor(newRay, world, depth-1);
        return 0.5* (record.collisionNormal + Color(1));
    }
    auto t = 0.5*(unit_vector(currentRay.direction()).y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

void CoreLauncher::launch(const char* fileName){


    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;

    constexpr double VIEWPORT_HEIGHT = 2.0;
    constexpr double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
    double focalLength = 1;
    Ray cameraRay(Point3(0,0,0), Vec3(0,0,-focalLength));
    auto horizontal = Vec3(VIEWPORT_WIDTH, 0, 0);
    auto vertical = Vec3(0, VIEWPORT_HEIGHT, 0);
    auto lowerLeftCorner = cameraRay.origin() - horizontal/2 - vertical/2 - Vec3(0, 0, focalLength);

    RayHittableList world;
    world.add(make_shared<SphereHittable>(Point3(0,-100.5,-1), 100.0));
    world.add(make_shared<SphereHittable>(Point3(0,0,-1), 0.5));


   
    FILE* file;
    file = fopen(fileName, "w+");
    std::cout << "'" << fileName << "'\n";
    fprintf(file, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    Ray currentRay;
    for(double y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(double x = 0; x < IMAGE_WIDTH; x++){
            Color pixelColor;
            for (int s = 0; s < 100; ++s) {
                double U = (x + random_double()) / (IMAGE_WIDTH-1);
                double V = (y + random_double()) / (IMAGE_HEIGHT-1);
                currentRay.orig = cameraRay.origin();
                currentRay.dir = lowerLeftCorner + U*horizontal + V*vertical - currentRay.orig;
                currentRay.dir = currentRay.dir / currentRay.dir.length();

                pixelColor += getRayColor(currentRay, world);
            }
            pixelColor /= 100.0;

            //std::cout << "\nU, V = (" << U << ", " << V << ")\n";
            
            //currentRay.dir = lowerLeftCorner + U*horizontal + V*vertical - currentRay.orig;
            //std::cout << "\ncameraDir = (" << currentRay.dir.x() << ", " << currentRay.dir.y() << ", " << currentRay.dir.z() <<  ")\n";
            //currentRay.dir = currentRay.dir / currentRay.dir.length();
            //pixelColor = getRayColor(currentRay, world);
            fprintf(file, "%d %d %d\n",(int)(256 * clamp(pixelColor.e[0],0,0.999)),(int)(256 * clamp(pixelColor.e[1],0,0.999)),(int)(256 * clamp(pixelColor.e[2],0,0.999)));
            
        }
    }
    fclose(file);

    std::cerr << "\nDone.\n";

}