#include "pch.h"
#include "Scene.h"

using namespace Engine;

bool Scene::initialized;

Scene::Scene()
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

	logInfo("Loading up TestModel.");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	testmodel = new Model();
}


Scene::~Scene()
{
}

void Scene::render(glm::mat4 view, glm::mat4 projection) {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	testmodel->rotate(sin((float)glfwGetTime() * 0.002f), glm::vec3(1.0f, 1.0f, 1.0f));
	testmodel->draw(view, projection);
}