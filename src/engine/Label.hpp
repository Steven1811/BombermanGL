#pragma once
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H


#define VERTEX_SHADER_PATH "../shaders/vertexShader.vert"
#define FRAGMENT_SHADER_PATH "../shaders/fragShader.frag"

class Label
{
private:
	std::string text;
public:
	Label(std::string text, float posX, float posY);
	void draw();
	~Label();
};

