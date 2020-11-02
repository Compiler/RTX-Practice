#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Core.h>
#include <maths/Camera.h>
#include <maths/Vec3.h>
#include <maths/Ray.h>
#include <maths/DiffuseMethods.h>

#include <RayHittables/Sphere.h>
#include <RayHittables/HittableList.h>

#include <Materials/Metal.h>
#include <Materials/Material.h>
#include <Materials/LambertianDiffuse.h>
#include <Materials/Dialectric.h>

#include <vector>


class Launcher{

    public:
        static std::vector<unsigned char> PIXELDATA;
        static int DIFFUSE_TYPE;

        void launch(const char* fileName);

};
