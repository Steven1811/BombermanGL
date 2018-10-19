#include "pch.h"
#include "Scene.hpp"

using namespace Engine;

bool Scene::initialized;

Scene::Scene(Window* window)
{
	if (!initialized) {
		logInfo("GLEW not initialized. Initializing for the first time.");
		GLenum err = glewInit();

		if (GLEW_OK != err)
		{
			logError("Error during GLEW initialization: %s", glewGetErrorString(err));
		}
		else {
			logInfo("Scene::Scene(): GLEW v%s initialized.", glewGetString(GLEW_VERSION));
			initialized = true;
		}
	}
	else {
		logInfo("GLEW already initialized. Skipping initialization.");
	}

	cam = new Camera(window);

	logInfo("Loading up TestModel.");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	testmodel = new Model();
	glEnable(GL_DEPTH_TEST);

}

void Scene::setBackgroundColor(unsigned int r, unsigned int g, unsigned int b) {
	backColor.r = (float)r * (1.f / 255.f);
	backColor.g = (float)g * (1.f / 255.f);
	backColor.b = (float)b * (1.f / 255.f);
}

Scene::~Scene()
{
}

void Scene::recompileShaders() {
	testmodel->getShader()->compile();
}

void Scene::render() {
	glClearColor(backColor.r, backColor.g, backColor.b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	testmodel->rotate(sin((float)glfwGetTime() * 0.2f), glm::vec3(1.0f, 1.0f, 1.0f));
	testmodel->draw(cam->getViewMatrix(), cam->getProjectionMatrix());
}