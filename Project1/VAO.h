#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include<glew.h>
#include<glfw3.h>
#include"Attribute.h"
#include"VBO.h"
#include"EBO.h"

class VertexArrayObject
{
private:
	GLuint handle;
	Attribute* attributelist = nullptr;
	VertexBufferObject* vbo = nullptr;
	ElementBufferObject* ibo = nullptr;
	GLint Numberofattributes;
	GLint maxattributes;
public:
	VertexArrayObject(GLint numberofattribs);
	void AddAttribute(GLint index, Attribute attribute);
	void SetVBO(VertexBufferObject* VBO);
	void SetIBO(ElementBufferObject* IBO);
	void Bind(void);
	void Unbind(void);
	void SetAttributes(void);
	void Draw(void);
	void Draw(GLint first, GLint count);
	~VertexArrayObject();
};