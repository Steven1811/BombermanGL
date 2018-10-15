#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logger.h"

namespace Engine {
	class Shader
	{
	private:
		unsigned int progId;
	public:
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		void use();
		void setBool(const std::string &name, bool value);
		void setInt(const std::string &name, int value);
		void setFloat(const std::string &name, float value);
		void setMat4(const std::string &name, glm::mat4* mat4);
		unsigned int getProgId();
	};
}
