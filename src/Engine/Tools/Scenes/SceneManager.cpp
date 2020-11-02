#include "SceneManager.h"

namespace reach{


    void SceneManager::update() {
		//swap scene requested
		if (_nextScene != _currentScene) _dirty = true;
		if (_dirty) {
			if(_nextScene != _currentScene) _scenes[_currentScene]->unload();
			_dirty = false;
			_currentScene = _nextScene;
			_scenes[_currentScene]->load();
		}
		_scenes[_currentScene]->update();
	}
	void SceneManager::render(){
		_scenes[_currentScene]->render();
	}

	void SceneManager::addScene(Scene* scene) {
		_scenes.push_back(scene);
		if (_currentScene == 255) _currentScene = 0;
	}
	// void SceneManager::addSceneRef(const Scene& scene) {
    //     Scene* ptr = new Scene(scene);
	// 	_scenes.emplace_back(ptr);
	// 	if (_currentScene == 255) _currentScene = 0;
	// }
	// void SceneManager::addScene(Scene scene) {
    //     Scene* ptr = new Scene(scene);
    //     _scenes.emplace_back(ptr);
	// 	if (_currentScene == 255) _currentScene = 0;
	// }


	void SceneManager::setCurrentScene(Scene scene) {
		const char* nextName = scene.getName();
		for (int i = 0; i < _scenes.size(); i++) {
			if (nextName == _scenes[i]->getName()) _nextScene = i;
		}

	}
	void SceneManager::setCurrentScene(const char* name) {
		for (int i = 0; i < _scenes.size(); i++) {
			if (name == _scenes[i]->getName()) _nextScene = i;
		}
	}
	void SceneManager::setCurrentScene(Scene* scene) {
		auto name = scene->getName();
		for (int i = 0; i < _scenes.size(); i++) {
			if (name == _scenes[i]->getName()) _nextScene = i;
		}
	}
	void SceneManager::setCurrentScene(uint8_t sceneIndex) {
		if (sceneIndex >= 0 && sceneIndex < _scenes.size()) _currentScene = sceneIndex;
	}


}