#include "RenderCore.h"

void RenderCore::load(){
    reach::StartupSystems::_initGLFW();
    _window = new reach::Window(1920, 1080, "RTX Engine", false);
    reach::StartupSystems::_initGlad();
    //reach::StartupSystems::_initTextureManager();
    reach::StartupSystems::_initImGUI(_window->getWindow());
    glfwSetWindowUserPointer(_window->getWindow(), this);
    //GLFWCallbacks::initCallBacks(_window);
    glfwSwapInterval(0);


    _rtx_textureID = reach::FileLoaderFactory::loadOpenGL_RTX_Texture();
    _program.loadShader("pass.vert", "pass.frag");

    
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _rtx_textureID);

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
    };

    glGenVertexArrays(1, &_vertexID);
    glBindVertexArray(_vertexID);

    glGenBuffers(1, &_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)  0                  ); // POSITION
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*) (3 * sizeof(float)) ); // COLOUR
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*) (6 * sizeof(float)) ); // TEXTURE COORDINATES
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    _program.use();
    glBindVertexArray(_vertexID);

}


void RenderCore::update(){
    if(glfwWindowShouldClose(_window->getWindow())) _isRunning = 0;
}

void RenderCore::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT);
    
    _program.use();
    glBindVertexArray(_vertexID);
    glDrawArrays(GL_TRIANGLES, 0, 6); 

    reach::InputManager::clear();
    glfwPollEvents();
    glfwSwapBuffers(_window->getWindow());
}

void RenderCore::unload(){

    REACH_LOG("Finished");

}