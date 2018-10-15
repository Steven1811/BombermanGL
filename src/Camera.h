#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
	class Camera
	{
	private:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 target = glm::vec3(1.0f, 0.0f, 0.0f);
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
		Camera();
		~Camera();
	};
}

