#include "pch.h"
#include "Model.hpp"

using namespace Engine;

Model::Model()
{
		 //Vertices				//Vertice Normals
	/*
	float vertices[] = {
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f, 0.0f, //Right Bottom Back
		 1.0f, -1.0f,  1.0f,	0.0f, 1.0f, 0.0f, //Right Bottom Front
		-1.0f, -1.0f,  1.0f,	0.0f, 1.0f, 0.0f, //Left Bottom Front
		-1.0f, -1.0f, -1.0f,	1.0f, 0.0f, 0.0f, //Left Bottom Back
		 1.0f,  1.0f, -1.0f,	1.0f, 0.0f, 0.0f, //Right Top Back
		 1.0f,  1.0f,  1.0f,	0.0f, 1.0f, 0.0f, //Right Top Front
		-1.0f,  1.0f,  1.0f,	0.0f, 1.0f, 0.0f, //Left Top Front
		-1.0f,  1.0f, -1.0f,	1.0f, 0.0f, 0.0f  //Left Top Back
	};
	*/

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	
	/*
	//Indices for GL_QUAD Rendering
	unsigned int indices[] = {
		0, 1, 2, 3,
		4, 7, 6, 5,
		0, 4, 5, 1,
		1, 5, 6, 2,
		2, 6, 7, 3,
		4, 0, 3, 7
	};
	*/
	shader = new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*/

	//Vertex Coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Vertex Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::draw(glm::mat4 view, glm::mat4 projection) {
	shader->use();
	glm::vec3 objColor = glm::vec3(0.7f, 0.7f, 0.7f);
	//glm::vec3 lightPos = glm::vec3(1.0f, 2.0f, -2.0f);
	glm::vec3 lightPos = glm::vec3(sin((float) glfwGetTime()) *2.5f, cos((float)glfwGetTime()) *2.5f, sin((float)glfwGetTime()) - 2.0f);
	glm::vec3 lightColor = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, -5.0f);
	shader->setMat4("model", &model);
	shader->setMat4("view", &view);
	shader->setInt("shininess", 32);
	shader->setFloat("specularStrength", 0.5f);
	shader->setVec3("viewPos", &viewPos);
	shader->setMat4("projection", &projection);
	shader->setFloat("ambientStrength", 1.0f);
	shader->setVec3("objectColor", &objColor);
	shader->setVec3("lightPos", &lightPos);
	shader->setVec3("lightColor", &lightColor);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

Model::~Model()
{
}

Shader* Model::getShader() {
	return this->shader;
}

void Model::rotate(float angle, glm::vec3 rotation) {
	model = glm::rotate(model, glm::radians(angle), rotation);
}