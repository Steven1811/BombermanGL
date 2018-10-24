#include "Game.hpp"
#include "../engine/Logger.hpp"

using namespace Engine;

Game::Game()
{
	Window* win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APPNAME);
	win->setFramerateLimit(60);

	Scene* scene = new Scene(win);
	scene->setBackgroundColor(54, 57, 62);
	win->setScene(scene);

	Model* model = new Model();
	model->translate(glm::vec3(-2.0f, 1.0f, -3.0f));
	Model* model2 = new Model();
	model2->translate(glm::vec3(2.0f, 0.0f, -3.0f));
	scene->addModel(model);
	scene->addModel(model2);

	//Called every by every Windows Message update
	win->addKeyCallback([&](Window* window, int key, int scancode, int action, int mods) -> void {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			logInfo("Closing window.");
			window->close();
		}
		#ifdef ENGINE_DEBUG
			if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
				window->getScene()->recompileShaders();
			}
		#endif
	});

	//Called every single Frame
	win->addRenderKeyCallback(GLFW_KEY_W, GLFW_PRESS, [&](Scene* scene, float deltaTime) -> void {
		scene->getCamera()->moveForward(CAM_SPEED * deltaTime);
	});
	win->addRenderKeyCallback(GLFW_KEY_S, GLFW_PRESS, [&](Scene* scene, float deltaTime) -> void {
		scene->getCamera()->moveForward(-CAM_SPEED * deltaTime);
	});
	win->addRenderKeyCallback(GLFW_KEY_A, GLFW_PRESS, [&](Scene* scene, float deltaTime) -> void {
		scene->getCamera()->moveRight(-CAM_SPEED * deltaTime);
	});
	win->addRenderKeyCallback(GLFW_KEY_D, GLFW_PRESS, [&](Scene* scene, float deltaTime) -> void {
		scene->getCamera()->moveRight(CAM_SPEED * deltaTime);
	});
	win->addRenderKeyCallback(GLFW_KEY_SPACE, GLFW_PRESS, [&](Scene* scene, float deltaTime) -> void {
		scene->getCamera()->moveUp(CAM_SPEED * deltaTime);
	});
	win->addRenderKeyCallback(GLFW_KEY_LEFT_CONTROL, GLFW_PRESS, [&](Scene* scene, float deltaTime) -> void {
		scene->getCamera()->moveUp(-CAM_SPEED * deltaTime);
	});

	win->addMouseCallback([&](Window* window, double xpos, double ypos) -> void {
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = MOUSE_SENSITIVITY;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.99f)
			pitch = 89.99f;
		if (pitch < -89.99f)
			pitch = -89.99f;
		window->getScene()->getCamera()->setDirection(pitch, yaw);
	});


	while (win->isOpen()) {
		model->rotate(sin(glfwGetTime() * 0.000002f), glm::vec3(1.0, 1.0, 0.0));
		model->setPosition(glm::vec3(sin(glfwGetTime() * 0.5f) * 5.0f, cos(glfwGetTime() * 0.5f) * 5.0f, 3.0f));
		model->setScale(glm::vec3((sin(glfwGetTime() * 0.5f)) + 1.0f, (cos(glfwGetTime() * 0.5f)) + 1.0f, (cos(glfwGetTime() * 0.5f)) + 1.0f));

		win->update();
	}
}


Game::~Game()
{
}
