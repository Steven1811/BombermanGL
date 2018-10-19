#include "pch.h"
#include "Camera.hpp"
#include "Window.hpp"

using namespace Engine;

Camera::Camera(Window* window)
{
	view = glm::translate(view, glm::vec3(0.0, 0.0, -5.0f));
	projection = glm::perspective(glm::radians(45.0), (double) window->getWidth() / (double) window->getHeight(), 1.0, 100.0);
}

glm::mat4 Camera::getViewMatrix() {
	return view;
}

glm::mat4 Camera::getProjectionMatrix() {
	return projection;
}

Camera::~Camera()
{
}
