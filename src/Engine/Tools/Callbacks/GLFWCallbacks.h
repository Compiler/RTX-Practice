#pragma once
#include <Engine/Rendering/Window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Engine/Tools/Input/InputManager.h>

class GLFWCallbacks {

#define GL_DEBUG_TYPE_ERROR 0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824E
#define GL_DEBUG_TYPE_PORTABILITY 0x824F
#define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#define GL_DEBUG_TYPE_OTHER 0x8251
public:
	GLFWCallbacks() = delete;
	GLFWCallbacks(const GLFWCallbacks&) = delete;

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	//void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	static void initCallBacks(reach::Window* _windowRef);

};