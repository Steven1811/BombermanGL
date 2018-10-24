#include "Camera.hpp"
#include "Window.hpp"

using namespace Engine;

Camera::Camera(Window* window)
{
	projection = glm::perspective(glm::radians(45.0), (double) window->getWidth() / (double) window->getHeight(), 1.0, 100.0);
	update();
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

void Camera::setDirection(float pitch, float yaw) {
	glm::vec3 cameraFront;
	cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraFront.y = sin(glm::radians(pitch));
	cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(cameraFront);
	update();
}

void Camera::update() {
	view = glm::lookAt(position, position + front, up);
}

void Camera::moveForward(float units) {
	position += units * front;
	update();
}

void Camera::moveUp(float units) {
	position.y += units;
	update();
}

void Camera::moveRight(float units) {
	position += glm::normalize(glm::cross(front, up)) * units;
	update();
}