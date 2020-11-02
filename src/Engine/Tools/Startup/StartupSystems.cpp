#include "StartupSystems.h"



namespace reach{

	void StartupSystems::_initTextureManager(){TextureManager::__init();}

	void StartupSystems::_initGLFW(){
		if(!glfwInit()){ REACH_DEBUG("Failed to init glfw");}
		else { REACH_DEBUG("GLFW initialized."); }
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//version 4.6 Core profile
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); 



	}
	void StartupSystems::_initGlad(){
		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) REACH_DEBUG("Failed to init glad");
		else { REACH_DEBUG("Glad initialized."); }


		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	

	}


	void StartupSystems::_initImGUI(GLFWwindow* window){
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGui_ImplOpenGL3_Init("#version 460");
		//ImGui_ImplGlfw_InitForOpenGL(window, true);
		//ImGui::StyleColorsDark();
//
	}

	void StartupSystems::initSubSystems(){
			_initGLFW();
			_initGlad();
			_initTextureManager();

	}

}