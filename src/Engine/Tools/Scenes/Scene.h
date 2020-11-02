#pragma once
#include <stdint.h>
#include <Engine/Tools/Logging/Logger.h>
#include <Engine/Rendering/ShaderProgram.h>
namespace reach{


    class Scene{
        private:
		    static uint8_t _COUNT;
        protected:
		    const char* m_sceneName;
        public:
            explicit Scene();
            explicit Scene(const char* name);

            virtual void load();
            virtual void update();
            virtual void render();
            virtual void unload();

            void setName(const char* name) {m_sceneName = name;};
            inline const char* getName()const { return m_sceneName; }

    };


}