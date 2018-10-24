#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Scene.hpp"

namespace Engine {
	typedef std::function<void(Window* window, int key, int scancode, int action, int mods)> keyCb;
	typedef std::function<void(Scene* scene, float deltaTime)> sceneCb;
	typedef std::function<void(Window* window, double xpos, double ypos)> mouseCb;

	struct sceneCallback {
		sceneCb scb;
		int key;
		int action;
		sceneCallback(sceneCb _sceneCallback, int _key, int _action) : scb(_sceneCallback), key(_key), action(_action) {}
	};

	class Window
	{
	private:
		std::vector<keyCb> keyCallbacks;
		std::vector<sceneCallback> sceneKeyCallbacks; //Called every frame
		std::vector<mouseCb> mouseCallbacks;

		unsigned int framerateLimit = 0;
		static bool initialized;
		static unsigned int windowCount;
		glm::vec3 backColor = glm::vec3(1.0f, 0.0f, 0.0f);
		int fBufWidth, fBufHeight = 0;
		Scene* scene;
		GLFWwindow* window;
		int frameCount = 0;
		double fps;
		static void error_callback(int error, const char* description);
		void initialize();
		void doRender();
		float deltaTime;
		float currentTime;
		float lastTime = 0;
		glm::mat4 view = glm::identity<glm::mat4>();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	public:
		Window(unsigned int width, unsigned int height, const char* windowTitle);
		~Window();
		void setKeyCallback(GLFWkeyfun key_callback);
		void setScene(Scene* scene);
		void update();
		bool hasActiveContext();
		void setContextActive();
		void setBackgroundColor(unsigned int r, unsigned int g, unsigned int b); //Only displayed, if no Scene is available.
		bool isOpen();
		double getFps();
		void setFramerateLimit(unsigned int framerate);
		int getWidth();
		int getHeight();
		glm::vec2 getSize();
		Scene* getScene();
		void close();
		void pollInput();
		void addKeyCallback(keyCb keyCallback);
		void addRenderKeyCallback(int key, int action, sceneCb keyCallback) {
			sceneKeyCallbacks.push_back(sceneCallback(keyCallback, key, action));
		}
		void addMouseCallback(mouseCb mouseCallback) {
			mouseCallbacks.push_back(mouseCallback);
		}
	protected:
		void triggerKeyCb(int key, int scancode, int action, int mods) { //Wrapper for Keycallbacks
			for (keyCb keyCallback : keyCallbacks) {
				keyCallback(this, key, scancode, action, mods);
			}
		}
		void triggerMouseCb(double xpos, double ypos) {
			for (mouseCb mouseCallback : mouseCallbacks) {
				mouseCallback(this, xpos, ypos);
			}
		}
	};
}
#endif