#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 
#include<glew.h>
#include<glfw3.h>

class VertexBufferObject
{
private:
	GLuint handle;
	GLfloat* vertexData = nullptr;
	GLint dataSize;

public:
	VertexBufferObject(GLfloat *vertices, GLint size);
	void Bind(void);
	void BufferData(GLenum DrawType);
	void Draw(GLint first, GLint count);
	void UnBind(void);
	~VertexBufferObject();
};
