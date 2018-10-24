#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include <SOIL.h>

namespace Engine {
	class Texture
	{
	private:
		GLuint tex;
	public:
		Texture();
		~Texture();
	};
}
#endif