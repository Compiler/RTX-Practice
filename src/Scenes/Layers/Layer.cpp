#include "Layer.h"
#include <string>
namespace reach{
    uint16_t Layer::_COUNT = 0;

	Layer::Layer() :m_layerName((std::string("Layer") + std::to_string(_COUNT++)).c_str()) {
		m_systemManager = new reach::SystemManager();
		m_renderer = new reach::BatchRenderer();
		m_renderer->init();
        m_shaderProgram = new ShaderProgram();
		m_registry = entt::registry();
		//m_registry.group<>();
	}
	Layer::Layer(const char* name) : m_layerName(name) {
		_COUNT++;
		m_systemManager = new reach::SystemManager();
		m_renderer = new reach::BatchRenderer();
		m_renderer->init();
		m_shaderProgram = new ShaderProgram();

       	m_registry = entt::registry();
	}


	void Layer::load() {
			REACH_LOG("Layer Loaded");
	}
	void Layer::update(){
		
	}
	void Layer::render(){
	}
	void Layer::unload(){
	}


}