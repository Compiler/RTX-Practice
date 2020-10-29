#include "Launcher.h"


int Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_VECTOR_DIFFUSE;


double RayHitSphere(const Point3& sphereCenter, double sphereRadius, const Ray& r);

Color RayColor(const Ray& r, const Hittable& world, int depth) {
    if(depth <= 0) return Color(0,0,0);
    HitRecord rec;
    if (world.hit(r, 0.001, _INFINITY_, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, world, depth-1);
        return Color(0,0,0);
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


void Launcher::launch(const char* fileName){

    HittableList world;
    auto material_ground = std::make_shared<LambertianDiffuse>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<LambertianDiffuse>(Color(0.7, 0.1, 0.1));
    auto material_left   = std::make_shared<Metal>(Color(0.5, 0.8, 0.8));
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.5));

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));

    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.25, material_left));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.25, material_right));
    

    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;
    constexpr int MAX_CHILD_RAYS = 50;
    constexpr int SPP = 100;

    Camera camera;

    FILE* file;
    file = fopen(fileName, "w+");
    fprintf(file, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
    for(int y = IMAGE_HEIGHT - 1; y >= 0; y--){
        std::cerr << "\rScanlines remaing: " << y << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++){
           Color pixelColor(0, 0, 0);
            for (int s = 0; s < SPP; ++s) {
                auto u = (x + random_double()) / (IMAGE_WIDTH-1);
                auto v = (y + random_double()) / (IMAGE_HEIGHT-1);
                Ray r = camera.getRay(u, v);
                pixelColor += RayColor(r, world, MAX_CHILD_RAYS);
            }
            auto r = pixelColor.x();
            auto g = pixelColor.y();
            auto b = pixelColor.z();

            // Divide the color by the number of samples.
            auto scale = 1.0 / SPP;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);
            int red = (int)(256 * clamp(r, 0.0, 0.999));
            int green = (int)(256 * clamp(g, 0.0, 0.999));
            int blue = (int)(256 * clamp(b, 0.0, 0.999));
            fprintf(file, "%d %d %d\n", red, green, blue);
        }
    }
    std::cerr << "\nDone.\n";
    fclose(file);
}