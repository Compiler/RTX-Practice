#include "CoreLauncher.h"


bool hitSphere(const Ray& currentRay, const Point3& sphereCenter, double sphereRadius){
    float t = dot(sphereCenter - currentRay.origin(), currentRay.direction());
    Point3 p = currentRay.at(t);
    double y = (sphereCenter-p).length();
    //std::cout << currentRay.direction().x() << ", " << currentRay.direction().y() << ", " << currentRay.direction().z() << "\n";
    //std::cout << y << " - " << sphereRadius << "\n";
    if(y > sphereRadius) return false;
    double x = sqrt(sphereRadius * sphereRadius - y*y);
    double t1 = t - x;
    double t2 = t + x;
    return true;

}

Color getRayColor(const Ray& currentRay){
    if (hitSphere(currentRay, Point3(0.5,0.5,1), 0.5))
        return Color(0);
    auto t = 0.5*(unit_vector(currentRay.direction()).y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

void CoreLauncher::launch(const char* fileName){


    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;
    constexpr int MAX_CHILD_RAYS = 50;
    constexpr int SPP = 100;
    constexpr int PIXEL_DENSITY =   2;


    Ray cameraRay;
    Point3 cameraOrigin = Point3(0, 0, -1);
    double cameraLeft = 0;
    double cameraRight = IMAGE_WIDTH;
    double cameraBot = 0;
    double cameraTop = IMAGE_HEIGHT;
    double cameraWidth = cameraRight - cameraLeft;
    double cameraHeight = cameraTop - cameraBot;

    cameraRay.orig = cameraOrigin;
    cameraRay.dir = Vec3(0, 0, -1);
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
            U -= 0.5;
            V -= 0.5;
            U *= IMAGE_WIDTH / IMAGE_HEIGHT;
            currentRay.orig = cameraRay.origin();
            currentRay.dir = cameraRay.dir + Vec3(U, V, 0);
            currentRay.dir = currentRay.dir / currentRay.dir.length();
            auto pixelColor = getRayColor(currentRay);
            fprintf(file, "%d %d %d\n",(int)(pixelColor.e[0]* 255), (int)(pixelColor.e[1]*255), (int)(pixelColor.e[2]*255));
            
        }
    }
    fclose(file);

    std::cerr << "\nDone.\n";

}