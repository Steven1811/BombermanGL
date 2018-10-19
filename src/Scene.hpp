#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Light.hpp"
#include "Camera.hpp"

namespace Engine{
	class Scene
	{
	private:
		std::vector<Model*> models;
		static bool initialized;
		Camera* cam;
		Model* testmodel;
		glm::vec3 backColor = glm::vec3(0.0f);
	public:
		Scene(Window* window);
		void setBackgroundColor(unsigned int r, unsigned int g, unsigned int b);
		void addModel(Model* model);
		void addLight(Light* light);
		void render();
		void recompileShaders();
		~Scene();
	};
}
#endif