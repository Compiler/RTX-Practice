#include "RenderCore.h"

void RenderCore::load(){
    reach::StartupSystems::_initGLFW();
    _window = new reach::Window(1920, 1080, "RTX Engine", false);
    reach::StartupSystems::_initGlad();
    //reach::StartupSystems::_initTextureManager();
    glfwSetWindowUserPointer(_window->getWindow(), this);
    GLFWCallbacks::initCallBacks(_window);
    glfwSwapInterval(0);

   
    // int tex_w = 512, tex_h = 512;
    // glGenTextures(1, &_computeTexture);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, _computeTexture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tex_w, tex_h, 0, GL_RGBA, GL_FLOAT, NULL);
    //glBindImageTexture(0, _computeTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);


    int work_grp_size[3];

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

    printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
    work_grp_size[0], work_grp_size[1], work_grp_size[2]);
    
    //_compute.loadComputeShader(REACH_INTERNAL_SHADER("rays.comp"));
    //glDispatchCompute((GLuint)tex_w, (GLuint)tex_h, 1);
    //glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    _program.loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));
     

    float a = 0.75f;
    float vertices[] = {
        // positions  texture coords
        -a,  -a, 0.0f,  0.0f, 1.0f,
        a,  -a, 0.0f,   1.0f, 1.0f,
        a,   a, 0.0f,   1.0f, 0.0f,
        -a,  -a, 0.0f,  0.0f, 1.0f,
        -a, a, 0.0f,    0.0f, 0.0f,
        a,  a, 0.0f,    1.0f, 0.0f,
    };

    glGenVertexArrays(1, &_vertexID);
    glBindVertexArray(_vertexID);

    glGenBuffers(1, &_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)  0                  ); // POSITION
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*) (3 * sizeof(float)) ); // TEXTURE COORDINATES
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    _rtx_textureID = reach::FileLoaderFactory::loadOpenGL_RTX_Texture();

}


void RenderCore::update(){
    if(glfwWindowShouldClose(_window->getWindow())) _isRunning = 0;
}

void RenderCore::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT);
    // _compute.use();
    // glDispatchCompute((GLuint)512, (GLuint)512, 1);
    // glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, _computeTexture);

    _program.use();
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _rtx_textureID);

    _program.uniform_set1Integer("textureVal", 0);
    //_program.use();
    glBindVertexArray(_vertexID);
    glDrawArrays(GL_TRIANGLES, 0, 6); 

    reach::InputManager::clear();
    glfwPollEvents();
    glfwSwapBuffers(_window->getWindow());
}

void RenderCore::unload(){

    REACH_LOG("Finished");

}