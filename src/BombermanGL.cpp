#include "pch.h"
#include <iostream>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Window.h"
#include "Scene.h"
#include "Game.h"

GLFWwindow* window;
GLFWwindow* window2;

unsigned int VBO, VAO, EBO;
unsigned int vertexShader, fragmentShader, shaderProgram;
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

using namespace Engine;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};

void renderCb(GLFWwindow* window, unsigned int fBufWidth, unsigned int fBufHeight) {
	
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		fprintf(stdout, "Closing window.\n");
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void render() {
	glClearColor(sin((float)glfwGetTime()), 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


int main() {
	Game* game = new Game();
	/*
	Window* win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APPNAME);
	Scene* scene = new Scene();
	//win->setRenderCallback(renderCb);
	win->setKeyCallback(key_callback);
	win->setBackgroundColor(255, 0, 255);
	glfwPollEvents();
	while (win->isOpen()) {
		glfwPollEvents();
		//printf("Window FPS %f\n", win->getFps());

		win->update();
	}
	*/
}


/*
int main()
{
	//Initialize GLFW
	glfwInit();
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APPNAME, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	else {
		std::cout << "Initialized GLFW window" << std::endl;
	}
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	Shader ourShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	//Setup Geometry
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//Set Draw Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
	projection = glm::ortho(-100.0, 100.0, -100.0, 100.0);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::ortho(0.0f,800.0f, 600.0f, 0.0f, 0.1f, 100.0f);
	int xpos, ypos, width, height = 0;
	float test = 0.0;
	//Main Event/Render Loop
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		glfwGetWindowPos(window, &xpos, &ypos);
		//processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.use();
		float radius = 10.0f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			test += 0.01;
			//projection = glm::perspective(glm::radians(test), (float) width / (float) height, 0.1f, 100.0f);
		}
		view = glm::lookAt(glm::vec3(test, 0.0, -3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0));

		ourShader.setMat4("model", &model);
		ourShader.setMat4("view", &view);
		ourShader.setMat4("projection", &projection);
		glViewport(0, 0, width, height);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
*/