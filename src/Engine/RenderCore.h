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
        unsigned int _rtx_textureID;
        bool _isRunning = true;


        unsigned int _vertexID, _bufferID;
    public:
        void load();
        void update();
        void render();
        void unload();
        inline bool isRunning() const {return _isRunning;}

};