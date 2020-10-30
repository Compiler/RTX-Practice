#include "CoreLauncher.h"


Color getRayColor(const Ray& currentRay){
    auto unitDirection = currentRay.dir;
    float t = 0.5 * unitDirection.e[1];
    return Color(t, 0, 0);
}

void CoreLauncher::launch(const char* fileName){


    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;
    constexpr int MAX_CHILD_RAYS = 50;
    constexpr int SPP = 100;
    constexpr int PIXEL_DENSITY =   2;


    Ray cameraRay;
    Point3 cameraOrigin = Point3(0, 0, -3);
    double cameraLeft = 0;
    double cameraRight = IMAGE_WIDTH;
    double cameraBot = 0;
    double cameraTop = IMAGE_HEIGHT;
    cameraRay.orig = cameraOrigin;
    cameraRay.dir = Vec3(0, 0, -1);
    FILE* file;
    file = fopen(fileName, "w+");
    std::cout << "'" << fileName << "'\n";
    fprintf(file, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    Ray currentRay;
    for(int y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++){
            double U = x / (IMAGE_WIDTH - 1);
            double V = y / (IMAGE_HEIGHT - 1);
            currentRay.orig = cameraRay.origin();
            currentRay.dir = Vec3(cameraLeft + x, cameraBot + y, cameraRay.dir[2]);
            auto pixelColor = getRayColor(currentRay);
            fprintf(file, "%d %d %d\n",(int)(pixelColor.e[0]), (int)(pixelColor.e[1]), (int)(pixelColor.e[2]));
            
        }
    }
    std::cerr << "\nDone.\n";
    fclose(file);


}