#include "Camera.hpp"
#include "Window.hpp"

using namespace Engine;

Camera::Camera(Window* window)
{
	updateProjectionMatrix(window->getWidth(), window->getHeight(), 45.0, 1.0, 100.0);
}

void Camera::updateProjectionMatrix(int windowWidth, int windowHeight, float fov, float minDistance, float maxDistance) {
	projection = glm::perspective(glm::radians(fov), (float) windowWidth / (float) windowHeight, minDistance, maxDistance);
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

glm::vec3 Camera::getPosition() {
	return position;
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

glm::vec3 Camera::getFront() {
	return front;
}