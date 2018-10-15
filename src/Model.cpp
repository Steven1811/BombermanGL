#include "pch.h"
#include "Model.h"

using namespace Engine;

Model::Model()
{
	//Vertices in 3D Space
	float vertices[] = {
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f
	};

	//Indices for GL_QUAD Rendering
	unsigned int indices[] = {
		0, 1, 2, 3,
		4, 7, 6, 5,
		0, 4, 5, 1,
		1, 5, 6, 2,
		2, 6, 7, 3,
		4, 0, 3, 7
	};
	shader = new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
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
}

void Model::draw(glm::mat4 view, glm::mat4 projection) {
	shader->use();
	shader->setMat4("model", &model);
	shader->setMat4("view", &view);
	shader->setMat4("projection", &projection);

	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
}

Model::~Model()
{
}

void Model::rotate(float angle, glm::vec3 rotation) {
	model = glm::rotate(model, glm::radians(angle), rotation);
}