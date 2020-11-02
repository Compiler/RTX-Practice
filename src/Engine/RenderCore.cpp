#include "RenderCore.h"

void RenderCore::load(){
    reach::StartupSystems::_initGLFW();
    _window = new reach::Window(1920, 1080, "RTX Engine", false);
    reach::StartupSystems::_initGlad();
    reach::StartupSystems::_initTextureManager();
    reach::StartupSystems::_initImGUI(_window->getWindow());
    glfwSetWindowUserPointer(_window->getWindow(), this);
    //GLFWCallbacks::initCallBacks(_window);
    glfwSwapInterval(0);


    _data.bitsPerPixel = 3;
    _data.fileName = "_Current_Image_.ppm";
    reach::FileLoaderFactory::loadOpenGLTexture(_data);

    _program.loadShader("pass.vert", "pass.frag");
}


void RenderCore::update(){
    if(glfwWindowShouldClose(_window->getWindow())) _isRunning = 0;
    reach::InputManager::clear();
    glfwPollEvents();
}

void RenderCore::render(){


    glfwSwapBuffers(_window->getWindow());
}

void RenderCore::unload(){

    REACH_LOG("Finished");

}