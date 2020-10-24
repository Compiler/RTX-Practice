
CXX = g++
C++_VERSION = c++17
CXXFLAGS = -std=$(C++_VERSION) -Wall -w -g -static-libgcc -static-libstdc++

OUT_DIR = bin
LAUNCHER_NAME = LukeRTX
SRC_DIR = src
ENTRY_POINT = src/main.cpp

#Libs
GLAD_ROOT = extern/glad/
GLAD_INC = $(GLAD_ROOT)include
GLAD_SRC = $(GLAD_ROOT)src

GLFW_ROOT = extern/glfw-3.3.2/MinGWmingw32/
GLFW_INC = $(GLFW_ROOT)include
GLFW_LIB = $(GLFW_ROOT)lib
GLFW_SRC = $(GLFW_ROOT)../src

STBIMAGE_ROOT = extern/stbimage

INC= -I $(SRC_DIR) -I $(GLAD_INC) -I $(GLFW_INC) -I $(STBIMAGE_ROOT)
LIBS = -L $(GLFW_LIB) #-L $(BOX2D_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32 #-lbox2d


SCENE_OBJS = $(OUT_DIR)/SceneManager.o $(OUT_DIR)/Scene.o 
LAYER_OBJS = $(OUT_DIR)/LayerManager.o $(OUT_DIR)/Layer.o


LIB_OBJS = $(RENDERING_OBJS) $(STARTUP_OBJS) $(FILE_OBJS) $(CALLBACK_OBJS) $(INPUT_OBJS) $(SCENE_OBJS) $(ECS_OBJS) $(UTIL_OBJS) $(LAYER_OBJS) $(CAMERA_OBJS)
OBJS =  $(REACH_ENGINE_OBJS) $(P_OBJS)#$(GAME_OBJS) #$(IMGUI_OBJS)
P_OBJS = $(P_REACH_ENGINE_OBJS)
LIB_OUT_OBJS = $(patsubst %.o, $(OUT_DIR)/%.o, $(LIB_OBJS))
OUT_OBJECTS = $(OBJS)#$(patsubst %.o, $(OUT_DIR)/%.o, $(OBJS))
P_OUT_OBJECTS = #$(patsubst %.o, $(OUT_DIR)/%.o, $(P_OBJS))
ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) 


main: $(ENTRY_POINT) $(OBJS)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $^ $(GLAD_SRC)/glad.c $(LINKS)
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe
	
static_lib:
	ar ru bin/libreachengine.a $(OUT_OBJECTS)

link: $(ENTRY_POINT)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(OUT_OBJECTS) $< $(GLAD_SRC)/glad.c $(LINKS)


ds: $(LAYER_OBJS) 
	make ReachCore.o
	make link
	ar ru bin/libreachengine.a $(LIB_OUT_OBJS)
	make run

$(LAYER_OBJS): $(OUT_DIR)/%.o: src/Scenes/Layers/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  


$(SCENE_OBJS): $(OUT_DIR)/%.o: src/Scenes/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  


run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe

launch:
	make
	make run