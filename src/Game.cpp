#include "pch.h"
#include "Game.hpp"
#include "Logger.hpp"
using namespace Engine;

Game::Game()
{
	Window* win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APPNAME);
	Scene* scene = new Scene(win);
	win->setScene(scene);
	win->addKeyCallback([&](Window* window, int key, int scancode, int action, int mods) -> void {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			logInfo("Closing window.");
			window->close();
		}
		#ifdef ENGINE_DEBUG
			if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
				window->getScene()->recompileShaders();
			}
		#endif
	});

	//Calls every single Frame
	win->addRenderKeyCallback(GLFW_KEY_W, GLFW_PRESS, [&](Scene* scene, int key, int action) -> void {
		printf("Hello from Renderer!\n");
	});
	win->addRenderKeyCallback(GLFW_KEY_A, GLFW_PRESS, [&](Scene* scene, int key, int action) -> void {
		printf("Hello too from Renderer!\n");
	});
	win->setBackgroundColor(255, 0, 255);
	win->setFramerateLimit(60);
	scene->setBackgroundColor(54, 57, 62);
	while (win->isOpen()) {
		win->update();
	}
}


Game::~Game()
{
}
