#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <Engine/Tools/Logging/Logger.h>
#include <Engine/Rendering/TextureManager.h>
// #include <imgui/imgui.h>
// #include <imgui/imgui_impl_opengl3.h>
// #include <imgui/imgui_impl_glfw.h>
namespace reach{
    //static class
    class StartupSystems{
        public:
            static void _initGLFW();
            static void _initGlad();
            static void _initImGUI(GLFWwindow* window);
            static void _initTextureManager();
            StartupSystems() = delete;
            StartupSystems operator=(const StartupSystems&) = delete;
            static void initSubSystems();
    };
}