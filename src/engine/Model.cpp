#include "Model.hpp"

using namespace Engine;

Model::Model()
{
	//3x Coordinates //3x Normals //2x TexCoordinates
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	shader = new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	diffuseTex = new Texture(DIFFUSE_MAP_PATH);
	specularTex = new Texture(SPECULAR_MAP_PATH);
	emissionTex = new Texture(EMISSION_MAP_PATH);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Vertex Coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Vertex Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::draw(Camera* cam) {
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {
		glm::vec3(10.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};

	shader->use();
	glm::vec3 lightPos = glm::vec3(sin((float) glfwGetTime()) *2.5f, cos((float)glfwGetTime()) *2.5f, sin((float)glfwGetTime()) - 2.0f);

	//Transformation Matrices
	shader->setMat4("model", &model);
	shader->setMat4("view", &cam->getViewMatrix());
	shader->setMat4("projection", &cam->getProjectionMatrix());

	//View position
	shader->setVec3("viewPos", &cam->getPosition());

	//Material
	shader->setVec3("material.ambient", &glm::vec3(1.0f, 0.5f, 0.31f));
	
	//Diffuse Map
	shader->setInt("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	diffuseTex->draw();

	//Specular Map
	shader->setInt("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	specularTex->draw();

	//Emission Map
	shader->setInt("material.emission", 2);
	glActiveTexture(GL_TEXTURE2);
	emissionTex->draw();

	shader->setFloat("material.shininess", 32.0f);

	//Time
	shader->setFloat("time", (float) glfwGetTime());

	//Light
	shader->setVec3("dirLight.ambient", &glm::vec3(0.3f, 0.24f, 0.14f));
	shader->setVec3("dirLight.diffuse", &glm::vec3(0.7f, 0.42f, 0.26f));
	shader->setVec3("dirLight.specular", &glm::vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3("dirLight.direction", &glm::vec3(-0.2f, -1.0f, -0.3f));

	shader->setVec3("pointLights[0].position", &glm::vec3(pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z));
	shader->setVec3("pointLights[0].ambient", &glm::vec3(pointLightColors[0].x * 0.1, pointLightColors[0].y * 0.1, pointLightColors[0].z * 0.1));
	shader->setVec3("pointLights[0].diffuse", &glm::vec3(pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z));
	shader->setVec3("pointLights[0].specular", &glm::vec3(pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z));
	shader->setFloat("pointLights[0].constant", 1.0f);
	shader->setFloat("pointLights[0].linear", 0.09f);
	shader->setFloat("pointLights[0].quadratic", 0.032f);

	shader->setVec3("spotLights[0].position", &cam->getPosition());
	shader->setVec3("spotLights[0].direction", &cam->getFront());
	shader->setVec3("spotLights[0].ambient", &glm::vec3(0.0f, 0.0f, 0.0f));
	shader->setVec3("spotLights[0].diffuse", &glm::vec3(0.0f, 3.0f, 0.0f));
	shader->setVec3("spotLights[0].specular", &glm::vec3(0.0f, 3.0f, 0.0f));
	shader->setFloat("spotLights[0].constant", 1.0f);
	shader->setFloat("spotLights[0].linear", 0.07f);
	shader->setFloat("spotLights[0].quadratic", 0.0017f);
	shader->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(7.0f)));
	shader->setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(10.0f)));

	shader->setVec3("spotLights[1].position", &(cam->getPosition()+glm::vec3(0.5f, 0.5f, 0.0f)));
	shader->setVec3("spotLights[1].direction", &cam->getFront());
	shader->setVec3("spotLights[1].ambient", &glm::vec3(0.0f, 0.0f, 3.0f));
	shader->setVec3("spotLights[1].diffuse", &glm::vec3(0.0f, 0.0f, 3.0f));
	shader->setVec3("spotLights[1].specular", &glm::vec3(0.0f, 0.0f, 3.0f));
	shader->setFloat("spotLights[1].constant", 1.0f);
	shader->setFloat("spotLights[1].linear", 0.07f);
	shader->setFloat("spotLights[1].quadratic", 0.0017f);
	shader->setFloat("spotLights[1].cutOff", glm::cos(glm::radians(7.0f)));
	shader->setFloat("spotLights[1].outerCutOff", glm::cos(glm::radians(10.0f)));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

Model::~Model()
{
}

void Model::update() {
	model = translationMatrix * scaleMatrix * rotationMatrix;
}

void Model::translate(glm::vec3 translation) {
	translationMatrix = glm::translate(translationMatrix, translation);
	update();
}

void Model::setPosition(glm::vec3 position) {
	this->translationMatrix = glm::identity<glm::mat4>();
	this->translationMatrix = glm::translate(this->translationMatrix, position);
	update();
}

Shader* Model::getShader() {
	return this->shader;
}

void Model::rotate(float angle, glm::vec3 rotation) {
	this->rotationMatrix = glm::rotate(this->rotationMatrix, angle, rotation);
	update();
}

void Model::setScale(glm::vec3 scale) {
	this->scaleMatrix = glm::identity<glm::mat4>();
	scaleMatrix = glm::scale(scaleMatrix, scale);
	update();
}

void Model::setRotation(float pitch, float yaw, float roll) {
	this->rotationMatrix = glm::identity<glm::mat4>();
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(yaw), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
	update();
}