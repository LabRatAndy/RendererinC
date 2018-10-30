#include "Camera.h"

void Camera::UpdateCameraVectors(void)
{
	glm::vec3 Front;
	Front.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));
	Front.y = sin(glm::radians(pitch));
	Front.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));
	front = glm::normalize(Front);
	right = glm::normalize(glm::cross(front, worldup));
	up = glm::normalize(glm::cross(right, front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->positiion = position;
	this->worldup = up;
	this->yaw = yaw;
	this->pitch = pitch;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix(void)
{
	return glm::lookAt(positiion, positiion + front, worldup);
}

void Camera::ProcessKeyboard(camera_movement direction, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;
	if (direction == Forward)
	{
		positiion += front * velocity;
	}
	if (direction == Backward)
	{
		positiion -= front * velocity;
	}
	if (direction == Left)
	{
		positiion -= right * velocity;
	}
	if (direction == Right)
	{
		positiion += right * velocity;
	}
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	yaw += xOffset;
	pitch += yOffset;
	if (constrainPitch)
	{
		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;
	}
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset)
{
}

GLfloat Camera::GetZoom(void)
{
	return zoom;
}

glm::vec3 Camera::GetPosition(void)
{
	return positiion;
}

glm::vec3 Camera::GetFront(void)
{
	return front;
}
