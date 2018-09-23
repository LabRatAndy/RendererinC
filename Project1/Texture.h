#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<src\SOIL.h>

class Texture
{
private:
	GLuint handle;
	GLboolean Cubemapped;
public:
	Texture(const GLchar* texturefilename);
	Texture(const GLchar* top, const GLchar* bottom, const GLchar* left, const GLchar* right, const GLchar* front, const GLchar* back);
	~Texture();
	void Bind();
	void Unbind();
	GLboolean IsCubeMapped();
	void SetTexParameterI(GLenum parametername, GLint parameter);
};