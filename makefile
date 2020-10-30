
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

CORE_LAUNCHER_OBJS = $(OUT_DIR)/CoreLauncher.o
MATHS_OBJS = $(OUT_DIR)/Vec3.o $(OUT_DIR)/Camera.o $(OUT_DIR)/Ray.o
HITTABLE_OBJS = $(OUT_DIR)/HittableList.o $(OUT_DIR)/Sphere.o
CORE_OBJS = $(OUT_DIR)/Launcher.o
MATERIAL_OBJS = $(OUT_DIR)/LambertianDiffuse.o $(OUT_DIR)/Metal.o
OBJS = $(CORE_LAUNCHER_OBJS) $(CORE_OBJS) $(MATHS_OBJS) $(HITTABLE_OBJS) $(MATERIAL_OBJS)
LIB_OUT_OBJS = $(patsubst %.o, $(OUT_DIR)/%.o, $(LIB_OBJS))
ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) 


main: $(ENTRY_POINT) $(OBJS)
	$(ALL_SETTINGS) -o $(OUT_DIR)/$(LAUNCHER_NAME) $^ $(GLAD_SRC)/glad.c $(LINKS)
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe
	


$(CORE_OBJS): $(OUT_DIR)/%.o: src/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(CORE_LAUNCHER_OBJS): $(OUT_DIR)/%.o: src/OtherLauncher/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(MATHS_OBJS): $(OUT_DIR)/%.o: src/maths/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  

$(HITTABLE_OBJS): $(OUT_DIR)/%.o: src/RayHittables/%.cpp
	$(ALL_SETTINGS) -c $< -o $@ 

$(MATERIAL_OBJS): $(OUT_DIR)/%.o: src/Materials/%.cpp
	$(ALL_SETTINGS) -c $< -o $@  	



run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe
