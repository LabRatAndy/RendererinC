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
	GLint count;
public:
	ElementBufferObject(GLint* ibo,GLint size);
	~ElementBufferObject();
	void Bind(void);
	void BufferData(GLenum drawtype);
	void Draw(void);
	void Unbind(void);
};