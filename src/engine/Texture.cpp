#include "Texture.hpp"

using namespace Engine;

Texture::Texture(const char* path)
{
	unsigned char* image;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	logInfo("Loading Texture from: %s", path);
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	if (image) {
		logInfo("Texture loaded: %s", path);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		logError("Error when loading Texture: %s", path);
	}
	SOIL_free_image_data(image);
}

GLuint Texture::getTextureId() {
	return textureId;
}

void Texture::draw() {
	glBindTexture(GL_TEXTURE_2D, textureId);
}

Texture::~Texture()
{
}
