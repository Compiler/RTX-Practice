#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <Engine/Tools/Logging/Logger.h>
#include <Launcher.h>
#define REACH_INTERNAL(x)         "src/Resources/" x
#define REACH_INTERNAL_SHADER(x)  REACH_INTERNAL("Shaders/") x
#define REACH_INTERNAL_TEXTURE(x) REACH_INTERNAL("Textures/") x
#define REACH_INTERNAL_MODEL(x)   REACH_INTERNAL("Models/") x
#define REACH_INTERNAL_SOUNDS(x)  REACH_INTERNAL("Sounds/") x


namespace reach {


    struct TextureData{
        uint8_t bitsPerPixel = 3;
        const char * fileName = "Default.png";
        uint32_t textureID;


    };

    namespace FileLoaderFactory{
        extern void loadTextFromFile(const char fileName[], std::string& dst);
        //rgba default composition
        extern unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, int req_comp = 4/*STBI_rgb_alpha = 4*/);
        void loadOpenGLTexture(reach::TextureData& comp);
        unsigned int loadOpenGL_RTX_Texture();
        extern void free(void* data);
    }
}