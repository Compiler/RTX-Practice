#pragma once
#include <Scenes/Scene.h>
#include <vector>
#include <stdio.h>
#include <stdint.h>

namespace lk{


    class SceneManager {
	private:
		std::vector<Scene*> _scenes;
		uint8_t _currentScene = 0;
		uint8_t _nextScene = 0;

		bool _dirty = true;
	public:

		SceneManager() = default;

		void update();
		void render();


		Scene* getSceneByName(const char* name) {
			for (int i = 0; i < _scenes.size(); i++) {
				if (name == _scenes[i]->getName()) return _scenes[i];
			}
		}

		void setCurrentScene(Scene scene);
		void setCurrentScene(const Scene& scene);
		void setCurrentScene(Scene* scene);
		void setCurrentScene(const char* name);
		void setCurrentScene(uint8_t sceneIndex);

		void addScene(Scene&& scene);
		void addScene(Scene* scene);
		void addSceneRef(const Scene& scene);
		void addScene(Scene scene);


		template<typename T>
		T* emplaceScene(){
			T* t = new T();
			_scenes.push_back(t);
			return t;
		}
		
		inline Scene& getCurrentScene() { return *_scenes[_currentScene]; }
		inline uint8_t getCurrentSceneIndex()const { return _currentScene; }


	};


}