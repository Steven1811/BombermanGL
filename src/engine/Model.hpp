#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#define VERTEX_SHADER_PATH "../shaders/vertexShader.vert"
#define FRAGMENT_SHADER_PATH "../shaders/fragShader.frag"
#define DIFFUSE_MAP_PATH "../models/textures/container2.png"
#define SPECULAR_MAP_PATH "../models/textures/container2_specular.png"
#define EMISSION_MAP_PATH "../models/textures/matrix.png"

namespace Engine{
	class Model
	{
	private:
		Texture* diffuseTex;
		Texture* specularTex;
		Texture* emissionTex;
		Shader* shader;
		unsigned int VBO; //Vertex Buffer Object
		unsigned int EBO; //Element Buffer Object
		unsigned int VAO; //Vertex Array Object
		glm::mat4 scaleMatrix = glm::identity<glm::mat4>();
		glm::mat4 translationMatrix = glm::identity<glm::mat4>();
		glm::mat4 rotationMatrix = glm::identity<glm::mat4>();
		glm::mat4 model = glm::identity<glm::mat4>();

	public:
		Model();
		void translate(glm::vec3 translation);
		void setPosition(glm::vec3 position);
		void setRotation(float pitch, float yaw, float roll);
		void rotate(float angle, glm::vec3 rotation);
		void draw(Camera* cam);
		void setScale(glm::vec3);
		void update();
		Shader* getShader();
		~Model();
	};
}
#endif