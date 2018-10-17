#include "pch.h"
#include "Game.h"

using namespace Engine;

Game::Game()
{
	Window* win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APPNAME);
	Scene* scene = new Scene();
	win->setScene(scene);
	//win->setRenderCallback(renderCb);
	/* Wrapper Callback Needed!
	win->setKeyCallback([](Window* window, int key, int scancode, int action, int mods)) */
	win->setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) mutable {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			fprintf(stdout, "Closing window.\n");
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->getScene()->recompileShaders();
		}
	});
	win->setBackgroundColor(255, 0, 255);
	win->setFramerateLimit(60);
	glfwPollEvents();
	scene->setBackgroundColor(54, 57, 62);
	while (win->isOpen()) {
		glfwPollEvents();
		win->update();
	}
}


Game::~Game()
{
}
