#include "Window.hpp"

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

	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->triggerKeyCb(key, scancode, action, mods);
	});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->triggerMouseCb(xpos, ypos);
	});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Window* usrWindow = (Window*) glfwGetWindowUserPointer(window);
		Scene* scene = usrWindow->getScene();
		if (scene) {
			scene->getCamera()->updateProjectionMatrix(width, height, 45.0, 1.0, 100.0);
		}
	});

	setContextActive();
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

	//imgui Initialization
	#ifdef ENGINE_DEBUG
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui_ImplGlfw_InitForOpenGL(window, false);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGui::StyleColorsDark();
	#endif
}

void Window::pollInput() {
	//Process Key Callbacks every frame
	for (struct sceneCallback sSceneKeyCallback : sceneKeyCallbacks) {
		if (glfwGetKey(window, sSceneKeyCallback.key) == sSceneKeyCallback.action)
			sSceneKeyCallback.scb(this->scene, deltaTime);
	}
}

void Window::doRender() {
	//imgui New Frame and Render Calls
	#ifdef ENGINE_DEBUG
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		ImGui::Render();
	#endif

	//If no scene was added to the window, draw the default background color
	if (!scene) {
		glClearColor(backColor.r, backColor.g, backColor.b, 1.);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else {
		//Draw Scene
		scene->render();
	}

	//Render imgui Data to OpenGL Context
	#ifdef ENGINE_DEBUG
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	#endif

	//Clear Screen and swap Backbuffer with Frontbuffer
	glfwSwapBuffers(window);
}

void Window::update() {
	currentTime = glfwGetTime();
	frameCount++;

	//Check if framerateLimiting is enabled
	if (framerateLimit != 0) {
		if (currentTime - lastTime >= 1.0 / (float)framerateLimit) {
			pollInput();
			doRender();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			fps = 1 / deltaTime;
			frameCount = 0;
		}
	}
	else {
		doRender();
	}
	
	glfwPollEvents();
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

void Window::setFramerateLimit(unsigned int framerate) {
	logInfo("FramerateLimit set to %i", framerate);
	this->framerateLimit = framerate;
}

Scene* Window::getScene() {
	return this->scene;
}

glm::vec2 Window::getSize() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return glm::vec2(width, height);
}

int Window::getWidth() {
	return getSize().x;
}

int Window::getHeight() {
	return getSize().y;
}

void Window::addKeyCallback(keyCb keyCallback) {
	keyCallbacks.push_back(keyCallback);
}

void Window::close() {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::showCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::hideCursor() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}