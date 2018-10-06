#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 
#include<GL\glew.h>
#include<GLFW\glfw3.h>

class VertexBufferObject
{
private:
	GLuint handle;
	GLfloat* vertexData = nullptr;

public:
	VertexBufferObject(GLfloat* vertices);
	void Bind(void);
	void BufferData(GLenum DrawType);
	void Draw(GLint first, GLint count);
	void UnBind(void);
	~VertexBufferObject();
};
