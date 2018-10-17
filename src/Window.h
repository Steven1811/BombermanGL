#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Scene.h"
#include "Logger.h"
#include "Model.h"

namespace Engine {

	typedef void(*RenderCb)(GLFWwindow* window, unsigned int fBufWidth, unsigned int fBufHeight);
	class Window
	{
	private:
		unsigned int framerateLimit = 0;
		static bool initialized;
		static unsigned int windowCount;
		glm::vec3 backColor = glm::vec3(1.0f, 0.0f, 0.0f);
		int fBufWidth, fBufHeight = 0;
		Scene* scene;
		GLFWwindow* window;
		RenderCb  renderCb;
		Camera* viewport;
		double previousTime = glfwGetTime();
		int frameCount = 0;
		double fps;
		static void error_callback(int error, const char* description);
		void initialize();
		void doRender();
		glm::mat4 view = glm::identity<glm::mat4>();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		void keyCbImpl();
	public:
		Window(unsigned int width, unsigned int height, const char* windowTitle);
		~Window();
		void setKeyCallback(GLFWkeyfun key_callback);
		//void setRenderCallback(RenderCb  renderCb);
		void setScene(Scene* scene);
		void update();
		bool hasActiveContext();
		void setContextActive();
		void setBackgroundColor(unsigned int r, unsigned int g, unsigned int b); //Only displayed, if no Scene is available.
		bool isOpen();
		double getFps();
		void setFramerateLimit(unsigned int framerate);
		Scene* getScene();
	};
}
