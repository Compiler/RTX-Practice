#pragma once
#include <Engine/Rendering/Window.h>
#include <Engine/Rendering/ShaderProgram.h>
#include <Engine/Tools/Startup/StartupSystems.h>
#include <Engine/Tools/Input/InputManager.h>
#include <Engine/Tools/Files/FileLoaderFactory.h>
#include <Engine/Rendering/TextureManager.h>
class RenderCore{
    private:
        reach::Window* _window;
        reach::ShaderProgram _program;
        reach::TextureData _data;
        bool _isRunning = true;
    public:
        void load();
        void update();
        void render();
        void unload();
        inline bool isRunning() const {return _isRunning;}

};