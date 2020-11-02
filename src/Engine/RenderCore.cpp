#include "RenderCore.h"

void RenderCore::load(){
    reach::StartupSystems::_initGLFW();
    _window = new reach::Window(1920, 1080, "RTX Engine", false);
    reach::StartupSystems::_initGlad();
    //reach::StartupSystems::_initTextureManager();
    glfwSetWindowUserPointer(_window->getWindow(), this);
    GLFWCallbacks::initCallBacks(_window);
    glfwSwapInterval(0);


    

    _program.loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));

    // float a = 0.75f;
    //  float vertices[] = {
    //      // positions          // colors           // texture coords
    //        -a,  -a, 0.0f,  0.0f, 0.0f,
    //         a,  -a, 0.0f,  1.0f, 0.0f,
    //         a,   a, 0.0f,  1.0f, 1.0f,
    //        -a,  -a, 0.0f,  0.0f, 0.0f,
    //         -a,   a, 0.0f,  0.0f, 1.0f,
    //         a,  a, 0.0f,  1.0f, 1.0f,
    //  };
    //  glGenVertexArrays(1, &_vertexID);
    //  glBindVertexArray(_vertexID);
    //  glGenBuffers(1, &_bufferID);
    //  glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
    //  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)  0                  ); // POSITION
    //  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*) (3 * sizeof(float)) ); // COLOUR
    //  glEnableVertexAttribArray(0);
    //  glEnableVertexAttribArray(1);
     glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
     glBindTexture(GL_TEXTURE_2D, _rtx_textureID);

    float a = 0.75f;
    float vertices[] = {
        // positions          // colors           // texture coords
        -a,  -a, 0.0f,  0.0f, 0.0f,
        a,  -a, 0.0f,  1.0f, 0.0f,
        a,   a, 0.0f,  1.0f, 1.0f,
        -a,  -a, 0.0f,  0.0f, 0.0f,
        -a,   a, 0.0f,  0.0f, 1.0f,
        a,  a, 0.0f,  1.0f, 1.0f,
    };

    glGenVertexArrays(1, &_vertexID);
    glBindVertexArray(_vertexID);

    glGenBuffers(1, &_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)  0                  ); // POSITION
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*) (6 * sizeof(float)) ); // TEXTURE COORDINATES
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);



    _rtx_textureID = reach::FileLoaderFactory::loadOpenGL_RTX_Texture();
    //_program.loadShader("pass.vert", "pass.frag");
    //glBindVertexArray(_vertexID);

}


void RenderCore::update(){
    if(glfwWindowShouldClose(_window->getWindow())) _isRunning = 0;
}

void RenderCore::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT);

    //_program.use();
    //glBindVertexArray(_vertexID);
    glDrawArrays(GL_TRIANGLES, 0, 6); 

    reach::InputManager::clear();
    glfwPollEvents();
    glfwSwapBuffers(_window->getWindow());
}

void RenderCore::unload(){

    REACH_LOG("Finished");

}