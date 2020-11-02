#pragma once
#include <Reach/Tools/Scenes/Scene.h>
#include <Reach/Tools/Scenes/Layers/DebugLayer.h>
#include <Reach/Tools/Scenes/Layers/DebugBackgroundLayer.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <Reach/Tools/Utils/MathHelpers.h>
namespace reach{

    class DebugScene : public Scene{
        private:
            DebugLayer layer1;
            DebugBackgroundLayer layer2;
        public:
            explicit DebugScene(){
                m_sceneName = "Debug Scene";
                REACH_DEBUG(layer1.getName() << " initialized.");
                REACH_DEBUG(layer2.getName() << " initialized.");
                m_layerManager.addLayer(&layer2);
                m_layerManager.addLayer(&layer1);
            }
            void load()override{
                REACH_WARN(m_sceneName << " Loading...");
            }
            void update()override{
                m_layerManager.update();
            }
            void render()override{
                m_layerManager.render();
            }
            void unload()override{
                REACH_WARN(m_sceneName << " Unloaded...");

            }

    };


}