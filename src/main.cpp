#pragma once
#include <Launcher.h>
#include <OtherLauncher/CoreLauncher.h>

int main(){

    CoreLauncher launcherCore;
    launcherCore.launch("_core_Current_Image.ppm");


    

    // Launcher launcher;
    // launcher.launch("_Current_Image_.ppm");
    // Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_HEMISPHERE_DIFFUSE;
    // launcher.launch("UNIT_HEMISPHERE_DIFFUSE.ppm");
    // Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_SPHERE_DIFFUSE;
    // launcher.launch("UNIT_SPHERE_DIFFUSE.ppm");
    // Launcher::DIFFUSE_TYPE = DiffuseMethods::UNIT_VECTOR_DIFFUSE;
    // launcher.launch("UNIT_VECTOR_DIFFUSE.ppm");
    return 0;
}