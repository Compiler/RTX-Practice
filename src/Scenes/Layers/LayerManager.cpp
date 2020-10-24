#include "LayerManager.h"

namespace lk{


    void LayerManager::update() {
		for(int i = 0; i < _layers.size(); i++)
			_layers[i]->update();
	}
	void LayerManager::render(){
		//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        //glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
		for(int i = 0; i < _layers.size(); i++)
			_layers[i]->render();
	}

	void LayerManager::addLayer(Layer* scene) {
		_layers.push_back(scene);
		if (_currentLayer == 255) _currentLayer = 0;
	}

	void LayerManager::setCurrentLayer(Layer scene) {
		const char* nextName = scene.getName();
		for (int i = 0; i < _layers.size(); i++) {
			if (nextName == _layers[i]->getName()) _nextLayer = i;
		}

	}
	void LayerManager::setCurrentLayer(const char* name) {
		for (int i = 0; i < _layers.size(); i++) {
			if (name == _layers[i]->getName()) _nextLayer = i;
		}
	}
	void LayerManager::setCurrentLayer(Layer* scene) {
		auto name = scene->getName();
		for (int i = 0; i < _layers.size(); i++) {
			if (name == _layers[i]->getName()) _nextLayer = i;
		}
	}
	void LayerManager::setCurrentLayer(uint8_t sceneIndex) {
		if (sceneIndex >= 0 && sceneIndex < _layers.size()) _currentLayer = sceneIndex;
	}


}