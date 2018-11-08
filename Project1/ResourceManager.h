#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include<glew.h>
#include<glfw3.h>
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include<map>
#include<vector>


class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();
	std::vector<Shader*> shaderList;
	std::vector<Texture*> textureList;
	std::vector<Camera*> cameraList;
	std::map<GLchar*,GLint> shaderDictionary;
	std::map<GLchar*,GLint> textureDictionary;
	std::map<GLchar*,GLint> cameraDictionary;
	
public:
	static ResourceManager& Instance(void);
	GLint AddShader(Shader* shader, GLchar* shadername);
	Shader* GetShader(GLint index);
	Shader* GetShader(GLchar* shadername);
	void RemoveShader(GLint index);
	void RemoveShader(GLchar* shadername);
	GLint AddCamera(Camera* camera, GLchar* cameraname);
	Camera* GetCamera(GLint index);
	Camera* GetCamera(GLchar* cameraname);
	void RemoveCamera(GLint index);
	void RemoveCamera(GLchar* cameraname);
	GLint AddTexture(Texture* texture, GLchar* texturename);
	Texture* GetTexture(GLint index);
	Texture* GetTexture(GLchar* texturename);
	void RemoveTexture(GLint index);
	void RemoveTexture(GLchar* texturename);
	//copy constructor and assignment operator diablement
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
};