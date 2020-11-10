#pragma once
#include <Launcher.h>
#include <Engine/RenderCore.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){


    
    
    RenderCore core;
    RenderCore::RENDER_MODE = RENDER_MODES::PARALLEL;
    //RenderCore::RENDER_MODE = RENDER_MODES::RTX;
    core.load();
    while(core.isRunning()){
        core.update();
        core.render();
    }
    core.unload();


    return 0;
}