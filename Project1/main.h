#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include<GLFW\glfw3.h>
#include<glm-0.9.9.0\glm\glm.hpp>
#include<glm-0.9.9.0\glm\gtc\matrix_transform.hpp>
#include<glm-0.9.9.0\glm\gtc\type_ptr.hpp>
#include<src\SOIL.h>
#include <iostream>
#include<fstream>
#include<sstream>

//cube
GLint cubeshader;
GLuint cubeVBO;
GLuint cubeVAO;
GLuint cubeIBO;
GLuint cubeTexture;
GLint cubevertexshader;
GLint cubefragmentshader;
GLint uniform_cubeModel;
GLint uniform_cubeView;
GLint uniform_cubeProjection;
GLint uniform_cubetexture;
GLint attribute_cube;
GLint attribute_cube_texcoords;
//skybox
GLint skyboxshader;
GLuint skyboxVBO;
GLuint skyboxVAO;
GLuint skyboxTexture;
GLint skyboxvertexshader;
GLint skyboxfragmentshader;
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
void LoadShader(const GLchar* filename, int Shadertype, GLint program, GLint* shader);
void LoadTexture(const GLchar* filename, GLuint* textureindex);
void LoadSkyBoxTexture(const std::string* filenames, GLuint* SkyboxIndex);
void  CreateCube(float size, GLfloat* cube);
void  CreateEBO(GLint* cube);
void  CreateSkyBoxCube(float size, GLfloat* skybox);
void UpdateFrame();
void RenderFrame();