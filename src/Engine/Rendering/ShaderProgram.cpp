#include "ShaderProgram.h"


namespace reach{
	

    uint32_t ShaderProgram::_loadShader(const char* fileName, int type){
        uint32_t shaderID;
		std::string shaderSrc;
		reach::FileLoaderFactory::loadTextFromFile(fileName, shaderSrc);
		const char* shaderSrcChar = shaderSrc.c_str();
        shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSrcChar, NULL);
		glCompileShader(shaderID);
		{
			int  success;
			char infoLog[512];
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                std::string shaderType;
                if(type == GL_VERTEX_SHADER) shaderType = "VERTEX";
                else if(type == GL_FRAGMENT_SHADER) shaderType = "FRAGMENT";
                else if(type == GL_GEOMETRY_SHADER) shaderType = "GEOMETRY";
                else if(type == GL_COMPUTE_SHADER) shaderType = "COMPUTE";
                else REACH_ERROR("SHADER::" << shaderType << "TYPE_UNKNOWN - TYPE = " << type);
				REACH_ERROR("SHADER::" << shaderType << "::COMPILATION_FAILED\t" <<  infoLog);
			}
		}

        return shaderID;

    }

    void ShaderProgram::loadComputeShader(const char* computeFile){
        uint32_t cid = _loadShader(computeFile, GL_COMPUTE_SHADER);
		_shaderProgram = glCreateProgram();

		glAttachShader(_shaderProgram, cid);
		glLinkProgram(_shaderProgram);

		{
			int  success;
			char infoLog[512];
			glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
				REACH_ERROR("ERROR::SHADER::COMP::COMPILATION_FAILED\t "<< infoLog );
			}
		}


		use();
		REACH_DEBUG("Loaded Shader '" << computeFile << "'");
	}


    void ShaderProgram::loadShader(const char* vertexFile, const char* fragmentFile){
        uint32_t vid = _loadShader(vertexFile, SHADER_TYPE_VERTEX);
        uint32_t fid = _loadShader(fragmentFile, SHADER_TYPE_FRAGMENT);


        _shaderProgram = glCreateProgram();

		glAttachShader(_shaderProgram, vid);
		glAttachShader(_shaderProgram, fid);
		glLinkProgram(_shaderProgram);

		{
			int  success;
			char infoLog[512];
			glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
				REACH_ERROR("ERROR::SHADER::COMP::COMPILATION_FAILED\t "<< infoLog );
			}
		}


		use();
		// GLint textureUnits;
		// glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
		// for(int i = 0; i < textureUnits; i++){
		// 	this->uniform_set1Integer(std::string(std::string("u_textures[") + std::to_string(i) + "]").c_str(), i, false);
		// }

		REACH_DEBUG("Loaded Shader '" << vertexFile << "' and '" << fragmentFile << "'");

    }


    void ShaderProgram::uniform_set1Integer(const char* name, int32_t value, bool print){
        int id = _check_uniform_(name, print);
		//REACH_LOG("setting uniform '" << name << "' to value " << value << " at uniform id " << id);
        glUniform1i(id, value);
        GLenum error = glGetError();
		if(error != GL_NO_ERROR)
			REACH_ERROR("OpenGL Error 'uniform_set1Integer' : " << error);
        
    }

    void ShaderProgram::uniform_set1Float(const char* name, float value){
  		int id = _check_uniform_(name, true);
        glUniform1fv(id, 1, &value);
        GLenum error = glGetError();
		if(error != GL_NO_ERROR)
			REACH_ERROR("OpenGL Error 'uniform_set1float' : " << error);

	}

	void ShaderProgram::uniform_set1Mat4(const char* name, const float* value){
  		int id = _check_uniform_(name, true);
        glUniformMatrix4fv(id, 1, GL_FALSE, value);
        GLenum error = glGetError();
		//if(error != GL_NO_ERROR)
			//REACH_ERROR("OpenGL Error 'uniform_set1Mat4' : " << error);

	}



}