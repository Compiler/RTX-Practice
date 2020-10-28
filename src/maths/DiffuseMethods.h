#pragma once
#include <maths/Vec3.h>

namespace DiffuseMethods{

    constexpr int UNIT_SPHERE_DIFFUSE = 0;
    constexpr int UNIT_VECTOR_DIFFUSE = 1;
    constexpr int UNIT_HEMISPHERE_DIFFUSE = 2;

    inline Vec3 random_in_hemisphere_diffuse(Vec3 hitRecordNormal){
        return random_in_hemisphere(hitRecordNormal);
    }

    inline Vec3 random_unit_vector_diffuse(){
        return random_unit_vector();
    }

    inline Vec3 random_in_unit_sphere_diffuse(){
        return random_in_unit_sphere();
    }

}