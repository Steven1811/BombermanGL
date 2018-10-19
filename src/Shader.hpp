#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logger.hpp"

namespace Engine {
	class Shader
	{
	private:
		GLuint progId;
		const char* vPath;
		const char* fPath;
		std::string vCode;
		std::string fCode;
	public:
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		void use();
		void setBool(const std::string &name, bool value);
		void setInt(const std::string &name, int value);
		void setFloat(const std::string &name, float value);
		void setMat4(const std::string &name, glm::mat4* mat4);
		void setVec3(const std::string &name, glm::vec3* vec3);
		void compile();
		unsigned int getProgId();
	};
}
#endif