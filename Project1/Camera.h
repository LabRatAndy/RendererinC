#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <glew.h>
#include<glfw3.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>

enum camera_movement
{
	Forward,
	Backward,
	Left,
	Right
};
//deafult values
const GLfloat YAW = 90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;
class Camera
{
private:
	glm::vec3 positiion;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldup;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;
	void UpdateCameraVectors(void);
public:
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw = YAW, GLfloat pitch = PITCH);
	glm::mat4 GetViewMatrix(void);
	void ProcessKeyboard(camera_movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(GLfloat yOffset);
	GLfloat GetZoom(void);
	glm::vec3 GetPosition(void);
	glm::vec3 GetFront(void);
};