#include "FileLoaderFactory.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>
#include <fstream>
#include <string>
namespace reach { namespace FileLoaderFactory{


    void loadTextFromFile(const char fileName[], std::string& dst){
        std::ifstream t(fileName);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        dst = str;
        if(dst.empty()) REACH_WARN("Couldn't open : '" << fileName << "'");
    }
	unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, int req_comp) {
		stbi_set_flip_vertically_on_load(true);
		return stbi_load(name, width, height, numOfColChannels, req_comp);
	}

    unsigned char* loadImagePPM(const char name[], int* width, int* height){
        FILE *fp;
        char buff[255];
        unsigned char* returned = new unsigned char[100000];

        fp = fopen(name, "r");
        fscanf(fp, "%s", returned);
        printf("1 : %s\n", buff );

        fgets(buff, 255, (FILE*)fp);
        printf("2: %s\n", buff );
        
        fgets(buff, 255, (FILE*)fp);
        printf("3: %s\n", buff );
        fclose(fp);
    }

    void loadOpenGLTexture(reach::TextureData& comp){
        unsigned int texture;
        glGenTextures(1, &texture);
        comp.textureID = texture;
        glBindTexture(GL_TEXTURE_2D, texture); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); 

        unsigned char *data = loadImage(comp.fileName, &width, &height, &nrChannels, comp.bitsPerPixel);
        if (data){
            if(comp.bitsPerPixel == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            if(comp.bitsPerPixel == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                
            glGenerateMipmap(GL_TEXTURE_2D);
        }else REACH_ERROR("Failed to load texture : '" << comp.fileName << "'");
        free(data);
    }

     unsigned int loadOpenGL_RTX_Texture(){
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); 

        GLubyte  *data = Launcher::PIXELDATA.data();
        if(Launcher::PIXELDATA.size() % 3 != 0) REACH_ERROR("Pixel Data not alligned");
        width = Launcher::WIDTH;
        height = Launcher::HEIGHT;
        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }else
            REACH_ERROR("Failed to load RTX texture \n");
        free(data);
    }


	void free(void* data) { stbi_image_free(data); }

}}