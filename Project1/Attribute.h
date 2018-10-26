#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Attribute
{
private:
	const GLchar* name;
	GLint size;
	GLint offset;
	GLint stride;
	GLuint index;
	GLenum type;
	GLenum normalised;
public:
	Attribute(const GLchar* Name, const GLuint Index, const GLint Size, const GLint Stride, const GLint Offset, GLenum Type,GLenum Normalised);
	Attribute();
	void SetAttribute();
	void EnableAttribute();
	void DisableAttribute();
};