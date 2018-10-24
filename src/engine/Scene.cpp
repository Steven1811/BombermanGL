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


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	for (Model* model : models) {
		model->getShader()->compile();
	}
}

void Scene::addModel(Model* model) {
	models.push_back(model);
}

void Scene::render() {
	glClearColor(backColor.r, backColor.g, backColor.b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Model* model : models) {
		model->draw(cam->getViewMatrix(), cam->getProjectionMatrix());
	}
	
}

Camera* Scene::getCamera() {
	return cam;
}