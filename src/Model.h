#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "Shader.h"

#define VERTEX_SHADER_PATH "../shaders/vertexShader.vert"
#define FRAGMENT_SHADER_PATH "../shaders/fragShader.frag"

namespace Engine {
	class Model
	{
	private:
		glm::mat4 model = glm::identity<glm::mat4>(); //Model Identity Matrice
		Shader* shader;

		unsigned int VBO; //Vertex Buffer Object
		unsigned int EBO; //Element Buffer Object
		unsigned int VAO; //Vertex Array Object

	public:
		Model();
		void rotate(float angle, glm::vec3 rotation);
		void draw(glm::mat4 view, glm::mat4 projection);
		~Model();
	};
}
