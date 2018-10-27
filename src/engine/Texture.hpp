#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include <SOIL.h>

#include "Logger.hpp"

namespace Engine {
	class Texture
	{
	private:
		int width, height = 0;
		GLuint textureId;
	public:
		Texture(const char* path);
		GLuint getTextureId();
		void draw();
		~Texture();
	};
}
#endif