#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engine {
	class Window;

	class Camera
	{
	private:
		float pitch, yaw, roll;
		glm::mat4 view = glm::identity<glm::mat4>();
		glm::mat4 projection;
		glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	public:
		void setPosition(glm::vec3 pos);
		void setPitch(float pitch);
		void setYaw(float yaw);
		void setRoll(float roll);
		void setRotation(glm::vec3 rot);
		void setOrthogonalProjection();
		void setPerspectiveProjection();
		void setFov(float fov);
		void setMinDistance(float distance);
		void setMaxDistance(float distance);
		void moveUp(float units);
		void update();
		void moveForward(float units);
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		void moveRight(float units);
		void setDirection(float pitch, float yaw);
		Camera(Window* window);
		~Camera();
	};
}
#endif