#pragma once
#include <Launcher.h>
#include <OtherLauncher/CoreLauncher.h>
#include <Engine/RenderCore.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){

    //CoreLauncher launcherCore;
    //launcherCore.launch("_core_Current_Image.ppm");

    RenderCore core;
    core.load();
    while(core.isRunning()){
        core.update();
        core.render();
    }
    core.unload();
    

    Launcher launcher;
    launcher.launch("_Current_Image_.ppm");


    return 0;
}