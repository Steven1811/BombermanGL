#include "pch.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define APPNAME "BombermanGL"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLFWwindow* window;
unsigned int VBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
unsigned int VAO;
unsigned int EBO;
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

void processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

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
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	//Compile VertexShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Check if VertexShader successfully compiled
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success) {
		std::cout << "VertexShader compile SUCCESS!" << std::endl;
	}
	else {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "VertexShader compile ERROR: " << infoLog << std::endl;
	}

	//Compile FragmentShader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Check if FragmentShader successfully compiled
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success) {
		std::cout << "FragmentShader compile SUCCESS!" << std::endl;
	}
	else {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "FragmentShader compile ERROR: " << infoLog << std::endl;
	}

	//Create linked ShaderProgram
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Check if linking the Shaderprogram failed
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success) {
		std::cout << "Linking ShaderProgram SUCCESS!" << std::endl;
	}
	else {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Linking ShaderProgram ERROR: " << infoLog << std::endl;
	}

	//Use the ShaderProgram and perform clean up
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Setup Geometry
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//Set Draw Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Main Event/Render Loop
	while (!glfwWindowShouldClose(window))
	{
		processInput();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
