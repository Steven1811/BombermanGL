#pragma once
#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Logger.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"

namespace Engine {
	class Scene
	{
	private:
		std::vector<Model*> models;
		static bool initialized;
		Camera cam;
		Model* testmodel;
	public:
		Scene();
		void setBackgroundColor(glm::vec3 backColor);
		void addModel(Model* model);
		void addLight(Light* light);
		void render(glm::mat4 view, glm::mat4 projection);
		~Scene();
	};
}
