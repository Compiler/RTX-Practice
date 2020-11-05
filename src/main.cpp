#pragma once
#include <Launcher.h>
#include <OtherLauncher/CoreLauncher.h>
#include <Engine/RenderCore.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){

    //CoreLauncher launcherCore;
    //launcherCore.launch("_core_Current_Image.ppm");

    

    //Launcher launcher;
    //launcher.launch("_Current_Image_.ppm");
    
    RenderCore core;
    RenderCore::RENDER_MODE = RENDER_MODES::PARALLEL;
    core.load();
    while(core.isRunning()){
        core.update();
        core.render();
    }
    core.unload();


    return 0;
}