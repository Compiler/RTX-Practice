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


Color getRayColor(const Ray& currentRay, const RayHittableList& world){
    
    RayHitRecord record;
    if(world.hit(currentRay, 0, INFINITY, record)){
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
   // world.add(make_shared<SphereHittable>(Point3(0,-100.5,-1), 100.0));
    world.add(make_shared<SphereHittable>(Point3(0,0,-1), 0.5));


   
    FILE* file;
    file = fopen(fileName, "w+");
    std::cout << "'" << fileName << "'\n";
    fprintf(file, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    Ray currentRay;
    for(double y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(double x = 0; x < IMAGE_WIDTH; x++){
            double U = x / (IMAGE_WIDTH - 1);
            double V = y / (IMAGE_HEIGHT - 1);
            //std::cout << "\nU, V = (" << U << ", " << V << ")\n";
            
            currentRay.orig = cameraRay.origin();
            currentRay.dir = lowerLeftCorner + U*horizontal + V*vertical - currentRay.orig;
            //std::cout << "\ncameraDir = (" << currentRay.dir.x() << ", " << currentRay.dir.y() << ", " << currentRay.dir.z() <<  ")\n";
            currentRay.dir = currentRay.dir / currentRay.dir.length();
            auto pixelColor = getRayColor(currentRay, world);
            fprintf(file, "%d %d %d\n",(int)(pixelColor.e[0]* 255), (int)(pixelColor.e[1]*255), (int)(pixelColor.e[2]*255));
            
        }
    }
    fclose(file);

    std::cerr << "\nDone.\n";

}