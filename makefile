
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

GLM_ROOT = extern/glm/

STBIMAGE_ROOT = extern/stbimage

INC= -I $(SRC_DIR) -I $(GLAD_INC) -I $(GLFW_INC) -I $(STBIMAGE_ROOT) -I $(GLM_ROOT)
LIBS = -L $(GLFW_LIB) #-L $(BOX2D_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32 #-lbox2d

CALLBACK_OBJS = $(OUT_DIR)/GLFWCallbacks.o
FILE_OBJS = $(OUT_DIR)/FileLoaderFactory.o
INPUT_OBJS = $(OUT_DIR)/InputManager.o
SCENE_OBJS = $(OUT_DIR)/SceneManager.o $(OUT_DIR)/Scene.o
STARTUP_OBJS = $(OUT_DIR)/StartupSystems.o
RENDERING_OBJS = $(OUT_DIR)/ShaderProgram.o $(OUT_DIR)/TextureManager.o $(OUT_DIR)/Window.o
MATHS_OBJS = $(OUT_DIR)/Vec3.o $(OUT_DIR)/Camera.o $(OUT_DIR)/Ray.o $(OUT_DIR)/AABB.o
HITTABLE_OBJS = $(OUT_DIR)/HittableList.o $(OUT_DIR)/Sphere.o $(OUT_DIR)/BVHNode.o
CORE_OBJS = $(OUT_DIR)/Launcher.o
RENDER_CORE_OBJS = $(OUT_DIR)/RenderCore.o
MATERIAL_OBJS = $(OUT_DIR)/LambertianDiffuse.o $(OUT_DIR)/Metal.o $(OUT_DIR)/Dialectric.o

OBJS = $(CORE_LAUNCHER_OBJS) $(CORE_OBJS) $(MATHS_OBJS) $(HITTABLE_OBJS) $(MATERIAL_OBJS) $(FILE_OBJS) $(INPUT_OBJS) $(SCENE_OBJS) $(STARTUP_OBJS) $(RENDERING_OBJS) $(RENDER_CORE_OBJS) $(CALLBACK_OBJS)


LIB_OUT_OBJS = $(patsubst %.o, $(OUT_DIR)/%.o, $(LIB_OBJS))
ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) 


main: $(ENTRY_POINT) $(OBJS)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $^ $(GLAD_SRC)/glad.c $(LINKS)
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe
	


$(CORE_OBJS): $(OUT_DIR)/%.o: src/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(RENDER_CORE_OBJS): $(OUT_DIR)/%.o: src/Engine/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(MATHS_OBJS): $(OUT_DIR)/%.o: src/maths/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(HITTABLE_OBJS): $(OUT_DIR)/%.o: src/RayHittables/%.cpp
	$(ALL_SETTINGS) -c $< -o $@ 

$(MATERIAL_OBJS): $(OUT_DIR)/%.o: src/Materials/%.cpp
	$(ALL_SETTINGS) -c $< -o $@ 

$(RENDERING_OBJS): $(OUT_DIR)/%.o: src/Engine/Rendering/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  	

$(STARTUP_OBJS): $(OUT_DIR)/%.o: src/Engine/Tools/Startup/%.cpp
	$(ALL_SETTINGS) -c $< -o $@ 

$(FILE_OBJS): $(OUT_DIR)/%.o: src/Engine/Tools/Files/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(CALLBACK_OBJS): $(OUT_DIR)/%.o: src/Engine/Tools/Callbacks/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(INPUT_OBJS): $(OUT_DIR)/%.o: src/Engine/Tools/Input/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(SCENE_OBJS): $(OUT_DIR)/%.o: src/Engine/Tools/Scenes/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  



run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe
