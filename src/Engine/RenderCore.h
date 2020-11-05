#pragma once
#include <Engine/Rendering/Window.h>
#include <Engine/Rendering/ShaderProgram.h>
#include <Engine/Tools/Startup/StartupSystems.h>
#include <Engine/Tools/Input/InputManager.h>
#include <Engine/Tools/Callbacks/GLFWCallbacks.h>
#include <Engine/Tools/Files/FileLoaderFactory.h>
#include <Engine/Rendering/TextureManager.h>

namespace RENDER_MODES{
    constexpr uint8_t PARALLEL = 0;
    constexpr uint8_t RTX = 1;
}
class RenderCore{
    private:
        reach::Window* _window;
        reach::ShaderProgram _program;
        GLuint _computeTexture;
        reach::ShaderProgram _compute;
        unsigned int _rtx_textureID;
        bool _isRunning = true;

        void _generalSetup();
        void _setupCompute();
        void _setupRTX();
        void _renderCompute();
        void _renderRTX();
        unsigned int _vertexID, _bufferID;
    public:
        static uint8_t RENDER_MODE;
        void load();
        void update();
        void render();
        void unload();
        inline bool isRunning() const {return _isRunning;}

};