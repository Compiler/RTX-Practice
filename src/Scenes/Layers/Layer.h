#pragma once

namespace lk{


    class Layer{

        private:
            static uint16_t _COUNT;
        protected:
            const char* m_layerName;

        public:
            explicit Layer();
            explicit Layer(const char* name);

            virtual void load();
            virtual void update();
            virtual void render();
            virtual void unload();

            const char* getName(){return m_layerName;}


    };

}