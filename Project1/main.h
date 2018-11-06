#pragma once
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include<SOIL.h>
#include <iostream>
#include<fstream>
#include<sstream>
#include "Shader.h"
#include "Texture.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

//cube
Shader* cubeshader;
VertexBufferObject* cubeVBO;
VertexArrayObject* cubeVAO;
ElementBufferObject* cubeIBO;
Texture* cubeTexture;
Attribute* cubePosition;
Attribute* cubeTexcoords;
GLint uniform_cubeModel;
GLint uniform_cubeView;
GLint uniform_cubeProjection;
GLint uniform_cubetexture;
GLint attribute_cube;
GLint attribute_cube_texcoords;
//skybox
Shader* skyboxshader;
VertexBufferObject* skyboxVBO;
VertexArrayObject* skyboxVAO;
Texture* skyboxTexture;
Attribute* skyboxPosition;
GLint uniform_skyboxView;
GLint uniform_skyboxProjection;
GLint uniform_skyboxtexture;
GLint attribute_skybox;
glm::vec3 camerapos;
glm::vec3 lookatpos;
glm::mat4 model;
glm::mat4 view;
glm::mat4 skyboxview;
glm::mat4 projection;


void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Error_Callback(int n, const char* error);
void initProgram();
void  CreateCube(float size, GLfloat* cube);
void  CreateEBO(GLint* cube);
void  CreateSkyBoxCube(float size, GLfloat* skybox);
void UpdateFrame();
void RenderFrame();