#pragma once
#include <Engine/Tools/Logging/Logger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace reach{

    class Window{

        private:
            const char* _windowName;
            GLFWwindow* _window;
        public:
            static float SCREEN_WIDTH;
            static float SCREEN_HEIGHT;

            Window() = default;
            Window(float width, float height, const char* name, bool fullscreen = false);

            void setTitle(const char* title){glfwSetWindowTitle(_window, title);}
            GLFWwindow* getWindow()const{return _window;}

    };


}