#include "pch.h"
#include "Window.h"

using namespace Engine;

bool Window::initialized;
unsigned int Window::windowCount;

void Window::error_callback(int error, const char* description) {
	//logError("Window Error %i: %s", error, description);
}

void Window::initialize() {
	glfwSetErrorCallback(error_callback);
	if (!initialized) {
		logInfo("GLFW not initialized yet. Initializing for the first time.");
		if (!glfwInit()) {
			logError("Error during GLFW Initialization!");
		}
		else {
			initialized = true;
			logInfo("GLFW Initialized!");
		}
	}
	else {
		logInfo("GLFW already initialized. Skipping initialization.");
	}
}

void Window::setKeyCallback(GLFWkeyfun key_callback) {
	GLFWkeyfun keycb = glfwSetKeyCallback(window, key_callback);
	if (!keycb) {
		logInfo("No previous key callback set. Setting key callback for the first time.");
	}
	else {
		logInfo("Old Key callback overriden.");
	}
}

Window::Window(unsigned int width, unsigned int height, const char* windowTitle)
{
	initialize();
	window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
	if (!window) {
		logError("Error during Window Creation!");
	}
	else {
		windowCount++;
		logInfo("Window created!");
	}
	setContextActive();
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
}

void Window::update() {
	//Count FPS
	double currentTime = glfwGetTime();
	frameCount++;

	if (currentTime - previousTime >= 1.0) {
		fps = frameCount;
		frameCount = 0;
		previousTime = currentTime;
	}

	//If no scene was added to the window, draw the default background color
	if (!scene) {
		glClearColor(backColor.r, backColor.g, backColor.b, 1.);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	//Draw Scene
	scene->render(view, projection);

	//Clear Screen and swap Backbuffer with Frontbuffer
	glfwSwapBuffers(window);
}

void Window::setContextActive() {
	logInfo("Active context set.");
	glfwMakeContextCurrent(window);
}

bool Window::hasActiveContext() {
	return glfwGetCurrentContext() == window;
}

void Window::setBackgroundColor(unsigned int r, unsigned int g, unsigned int b) {
	logInfo("Background color set!");
	backColor.r = (float) r * (1.f / 255.f);
	backColor.g = (float) g * (1.f / 255.f);
	backColor.b = (float) b * (1.f / 255.f);
}

bool Window::isOpen() {
	return !glfwWindowShouldClose(window);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	if (windowCount == 0) {
		glfwTerminate();
		logInfo("GLFW Terminated!");
		exit(EXIT_SUCCESS);
	}
}

double Window::getFps() {
	return fps;
}

void Window::setScene(Scene* scene) {
	this->scene = scene;
}