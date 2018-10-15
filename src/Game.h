#pragma once
#include <iostream>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Window.h"
#include "Scene.h"
#include "Game.h"

#define APPNAME "BombermanGL"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


class Game
{
public:
	Game();
	~Game();
};

