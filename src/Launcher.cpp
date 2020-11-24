#include "Launcher.h"


HittableList random_scene() {
    HittableList world;

    auto ground_Material = make_shared<LambertianDiffuse>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_Material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> Sphere_Material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    Sphere_Material = make_shared<LambertianDiffuse>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_Material));
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    Sphere_Material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_Material));
                } else {
                    // glass
                    Sphere_Material = make_shared<Dialectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_Material));
                }
            }
        }
    }

    auto Material1 = make_shared<Dialectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, Material1));

    auto Material2 = make_shared<LambertianDiffuse>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, Material2));

    auto Material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, Material3));

    return world;
}


int Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_VECTOR_DIFFUSE;
std::vector<unsigned char> Launcher::PIXELDATA;
int Launcher::WIDTH = 0;
int Launcher::HEIGHT = 0;

double RayHitSphere(const Point3& SphereCenter, double SphereRadius, const Ray& r);

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

Color RayColor(const Ray& r, const BVHNode& world, int depth) {
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

double RayHitSphere(const Point3& SphereCenter, double SphereRadius, const Ray& r){
    Vec3 oc = r.origin() - SphereCenter;
    float a = r.direction().length_squared();
    float halfB=  dot(oc, r.direction());     
    float c = oc.length_squared() - SphereRadius*SphereRadius;
    float discriminant = halfB * halfB - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-halfB - sqrt(discriminant) ) / a;
    }


}


void Launcher::launch(const char* fileName){

    HittableList world;
    //  for(double i = -1;i < 1; i+= 0.1){
    //      double cVal = (i+1) / 2.0;
    //      auto Material_back   = std::make_shared<Metal>(Color(cVal,cVal,cVal));
    //      world.add(std::make_shared<Sphere>(Point3( i, -0.25, -0.25), 0.05, Material_back));
    //  }
    auto Material_ground = std::make_shared<LambertianDiffuse>(Color(0.2, 0.9, 0.3));
    //auto Material_center = std::make_shared<LambertianDiffuse>(Color(0.3, 0.2, 0.5));
    auto checkered = std::make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9));
    auto Material_center = std::make_shared<LambertianDiffuse>(checkered);
    auto Material_left   = make_shared<Dialectric>(1.5);
    auto Material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    // auto Material_ground = std::make_shared<LambertianDiffuse>(Color(1,0,0));
    // auto Material_center = std::make_shared<LambertianDiffuse>(Color(1,0,0));
    // auto Material_left   = make_shared<Dialectric>(1.5);
    // auto Material_right  = std::make_shared<Metal>(Color(1,0,0), 0.0);
    world.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, Material_ground));
    world.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, Material_center));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, Material_left));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, Material_left));
    world.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, Material_right));
    //BVHNode node(world, 0, 0);

    //world = random_scene();

    constexpr double ASPECT_RATIO = 16.0/9.0;
    constexpr int IMAGE_WIDTH = 400;
    constexpr int IMAGE_HEIGHT = IMAGE_WIDTH / ASPECT_RATIO;
    Launcher::WIDTH = IMAGE_WIDTH;
    Launcher::HEIGHT = IMAGE_HEIGHT;
    constexpr int MAX_CHILD_RAYS = 50;
    constexpr int SPP = 100;
    constexpr int PIXEL_DENSITY =   2;

    Point3 lookfrom(0,2,3);
    Point3 lookat(0,0,-1);
    Vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera camera(lookfrom, lookat, vup, 20, ASPECT_RATIO, aperture, dist_to_focus, 0, 1);

    FILE* file;
    file = fopen(fileName, "w+");
    std::cout << "'" << fileName << "'\n";
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
                //pixelColor += RayColor(r, node, MAX_CHILD_RAYS);
            }
            auto r = pixelColor.x();
            auto g = pixelColor.y();
            auto b = pixelColor.z();

            // Divide the Color by the number of samples.
            auto scale = 1.0 / SPP;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);
            int red = (int)(256 * clamp(r, 0.0, 0.999));
            int green = (int)(256 * clamp(g, 0.0, 0.999));
            int blue = (int)(256 * clamp(b, 0.0, 0.999));
            fprintf(file, "%d %d %d\n", red, green, blue);
            unsigned char rred = red;
            unsigned char ggreen = green;
            unsigned char bblue = blue;
            PIXELDATA.push_back(rred);PIXELDATA.push_back(ggreen);PIXELDATA.push_back(bblue);
            // std::cout << red << "->" << (int)rred << "\n";
            // std::cout << green << "->" << (int)ggreen << "\n";
            // std::cout << blue << "->" << (int)bblue << "\n";
        }
    }
    std::cerr << "\nDone.\n";
    fclose(file);
}