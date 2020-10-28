#pragma once
#include <Launcher.h>

int main(){


    Launcher launcher;
    Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_HEMISPHERE_DIFFUSE;
    launcher.launch("UNIT_HEMISPHERE_DIFFUSE.ppm");
    Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_SPHERE_DIFFUSE;
    launcher.launch("UNIT_SPHERE_DIFFUSE.ppm");
    Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_VECTOR_DIFFUSE;
    launcher.launch("UNIT_VECTOR_DIFFUSE.ppm");
    return 0;
}