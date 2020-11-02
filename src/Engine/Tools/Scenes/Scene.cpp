#include "Scene.h"
#include <string>
namespace reach{
    uint8_t Scene::_COUNT = 0;

	Scene::Scene() :m_sceneName((std::string("Scene") + std::to_string(_COUNT++)).c_str()) {
	}
	Scene::Scene(const char* name) : m_sceneName(name) {
		_COUNT++;
	}


	void Scene::load() {
			REACH_LOG("Scene Loaded");
	}
	void Scene::update(){
		
	}
	void Scene::render(){
	}
	void Scene::unload(){
	}
}