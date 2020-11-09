#pragma once
#include <Core.h>
#include <iostream>
#include <cmath>

class Vec3{

    public:
        double e[3];

    public:
        Vec3();
        Vec3(double e012);
        Vec3(double e0, double e1, double e2);
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        Vec3 operator-() const;
        double& operator[](int i);
        Vec3& operator+=(const Vec3 &v);
        Vec3& operator*=(const double t);
        Vec3& operator/=(const double t);
        double length() const;
        double length_squared() const;

        inline static Vec3 random() {
            return Vec3(random_double(), random_double(), random_double());
        }

        inline static Vec3 random(double min, double max) {
            return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }


        inline void print(bool newLine = true){
            std::cout << "(" << e[0] << ", " << e[1] << ", " <<  e[2] << ")";
            if(newLine) std::cout << "\n";
        }
        






};

typedef Vec3 Point3;
typedef Vec3 Color;


inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}
inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vec3 random_unit_vector() {
    auto a = random_double(0, 2*_PI_);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z*z);
    return Vec3(r*cos(a), r*sin(a), z);
}

inline Vec3 random_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}


inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}