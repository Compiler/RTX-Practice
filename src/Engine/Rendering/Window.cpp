#include "Window.h"


namespace reach{

    float reach::Window::SCREEN_WIDTH;
    float reach::Window::SCREEN_HEIGHT;
    Window::Window(float width, float height, const char* name, bool fullscreen){
         Window::SCREEN_HEIGHT = height; Window::SCREEN_WIDTH = width; _windowName = name;
         _window = glfwCreateWindow(width, height, name, NULL, NULL);
         glfwMakeContextCurrent(_window);
    
         if(!_window){
		     REACH_ERROR("!!Failed to load window!!");
	     }

    }


}