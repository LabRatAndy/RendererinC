#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif 
#include<GL\glew.h>
#include<GLFW\glfw3.h>

class ElementBufferObject
{
private:
	GLuint handle;
	GLint* ibo = nullptr;
public:
	ElementBufferObject(GLint* ibo);
	~ElementBufferObject();
	void Bind(void);
	void BufferData(GLenum drawtype);
	void Unbind(void);
};