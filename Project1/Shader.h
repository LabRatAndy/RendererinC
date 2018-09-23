#pragma once
#define GLEW_STATIC
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>

class Shader
{
public:
	Shader(const GLchar* vertexShaderfile, const GLchar* fragmentShaderfile);
	~Shader();
	void Use();
	GLint GetAttributeHandle(const GLchar* name);
	GLint GetUniformHandle(const GLchar* name);
private:
	GLuint handle;
	GLuint vertexShader;
	GLuint fragmentShader;
	void LoadShader(const GLchar* filename, GLint shadertype);
};
