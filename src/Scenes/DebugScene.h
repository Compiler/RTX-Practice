#pragma once
#include <Scenes/Scene.h>
namespace reach{

    class DebugScene : public Scene{
        private:
        public:
            explicit DebugScene(){
                m_sceneName = "Debug Scene";
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