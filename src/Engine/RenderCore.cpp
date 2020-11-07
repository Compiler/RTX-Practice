#include "RenderCore.h"

uint8_t RenderCore::RENDER_MODE = RENDER_MODES::PARALLEL;
void RenderCore::_setupCompute(){
    int work_grp_size[3];

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
       
    tex_w = work_grp_size[0], tex_h = 1024;
    float ratio = 16.0f/ 9.0f;
    tex_h = tex_w / ratio;
    glGenTextures(1, &_computeTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _computeTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tex_w, tex_h, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindImageTexture(0, _computeTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);



    /*
    struct shader_data_t
    {
    float spherePositions[4];
    } shader_data;
    shader_data.spherePositions[0] = 4;
    shader_data.spherePositions[1] = 4;
    shader_data.spherePositions[2] = 4;
    shader_data.spherePositions[3] = 4;
    GLuint ssbo = 0;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(shader_data), &shader_data, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    memcpy(p, &shader_data, sizeof(shader_data));
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    GLuint block_index = glGetProgramResourceIndex(_compute.getShader(), GL_SHADER_STORAGE_BLOCK, "shader_data");
    GLuint ssbo_binding_point_index = 2;
    glShaderStorageBlockBinding(_compute.getShader(), block_index, ssbo_binding_point_index);
    glDispatchCompute((GLuint)512, (GLuint)512, 1);
    glShaderStorageBlockBinding(_compute.getShader(), block_index, 80);
    GLuint binding_point_index = 80;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point_index, ssbo);   */



    printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
    work_grp_size[0], work_grp_size[1], work_grp_size[2]);
    
    _compute.loadComputeShader(REACH_INTERNAL_SHADER("rays.comp"));

    glDispatchCompute((GLuint)tex_w, (GLuint)tex_h, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _computeTexture);

    _program.use();
    _program.uniform_set1Integer("textureVal", 0);


}
void RenderCore::_generalSetup(){

    float a = 0.95f;
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

    
    _program.loadShader(REACH_INTERNAL_SHADER("pass.vert"), REACH_INTERNAL_SHADER("pass.frag"));
    

}

void RenderCore::_setupRTX(){

     

    _rtx_textureID = reach::FileLoaderFactory::loadOpenGL_RTX_Texture();

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, _rtx_textureID);

    _program.use();
    _program.uniform_set1Integer("textureVal", 0);

}


void RenderCore::load(){
    reach::StartupSystems::_initGLFW();
    _window = new reach::Window(1920, 1080, "RTX Engine", false);
    reach::StartupSystems::_initGlad();
    //reach::StartupSystems::_initTextureManager();
    glfwSetWindowUserPointer(_window->getWindow(), this);
    GLFWCallbacks::initCallBacks(_window);
    glfwSwapInterval(0);

    _generalSetup();
    if(RenderCore::RENDER_MODE == RENDER_MODES::PARALLEL) _setupCompute();
    else if(RenderCore::RENDER_MODE ==RENDER_MODES::RTX) _setupRTX();



}


void RenderCore::update(){

    

    if(glfwWindowShouldClose(_window->getWindow())) _isRunning = 0;
}

void RenderCore::_renderCompute(){
        static float zPosition = 0;
        static float yPosition = 0;
        static float xPosition = 0;
    {
        _compute.use();
        static constexpr float DELTA = 0.025;
        if(reach::InputManager::isKeyPressed(reach::KeyCodes::KEY_D))xPosition +=DELTA;
        if(reach::InputManager::isKeyPressed(reach::KeyCodes::KEY_A))xPosition -=DELTA;
        if(reach::InputManager::isKeyPressed(reach::KeyCodes::KEY_W))yPosition -=DELTA;
        if(reach::InputManager::isKeyPressed(reach::KeyCodes::KEY_S))yPosition +=DELTA;
        if(reach::InputManager::isKeyPressed(reach::KeyCodes::KEY_UP))zPosition -=DELTA;
        if(reach::InputManager::isKeyPressed(reach::KeyCodes::KEY_DOWN))zPosition +=DELTA;
        
        REACH_LOG(zPosition);
        _compute.uniform_set1Float("u_delta_x", xPosition);
        _compute.uniform_set1Float("u_delta_y", yPosition);
        _compute.uniform_set1Float("u_delta_z", zPosition);


           
    }
    glDispatchCompute((GLuint)tex_w, (GLuint)tex_h, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    _program.use();
    _program.uniform_set1Integer("textureVal", 0);


    reach::InputManager::clear();
    glfwPollEvents();

}

void RenderCore::_renderRTX(){
    // _program.use();
    // glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    // glBindTexture(GL_TEXTURE_2D, _computeTexture);

}

void RenderCore::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(RenderCore::RENDER_MODE == RENDER_MODES::PARALLEL) _renderCompute();
    else if(RenderCore::RENDER_MODE == RENDER_MODES::RTX) _renderRTX();

    glBindVertexArray(_vertexID);
    glDrawArrays(GL_TRIANGLES, 0, 6); 

    reach::InputManager::clear();
    glfwPollEvents();
    glfwSwapBuffers(_window->getWindow());
}

void RenderCore::unload(){

    REACH_LOG("Finished");

}