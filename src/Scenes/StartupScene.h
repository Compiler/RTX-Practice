#pragma once
#include <Scenes/Scene.h>

namespace lk{

    class StartupScene : public Scene{
        private:
            StartupLayer layer1;
        public:
            explicit StartupScene(){
                m_sceneName = "Startup Scene";
                m_layerManager.addLayer(&layer2);
                m_layerManager.addLayer(&layer1);
            }
            void load()override{
            }
            void update()override{
                m_layerManager.update();
            }
            void render()override{
                m_layerManager.render();
            }
            void unload()override{
            }

    };


}