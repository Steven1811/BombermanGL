#include "pch.h"
#include "Game.h"

using namespace Engine;

Game::Game()
{
	Window* win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APPNAME);
	Scene* scene = new Scene();
	win->setScene(scene);

	//win->setRenderCallback(renderCb);
	win->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			fprintf(stdout, "Closing window.\n");
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	});
	win->setBackgroundColor(255, 0, 255);
	glfwPollEvents();
	while (win->isOpen()) {
		glfwPollEvents();
		//logInfo("Window FPS %f", win->getFps());

		win->update();
	}
}


Game::~Game()
{
}
