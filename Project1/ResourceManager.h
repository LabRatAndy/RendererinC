#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
//#define DEBUG
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
	std::map<GLchar*,Shader*> shaderDictionary;
	std::map<GLchar*,Texture*> textureDictionary;
	std::map<GLchar*,Camera*> cameraDictionary;
	
public:
	static ResourceManager& Instance(void);
	bool AddShader(Shader* shader, GLchar* shadername);
	Shader* GetShader(GLchar* shadername);
	void RemoveShader(GLchar* shadername);
	void AddCamera(Camera* camera, GLchar* cameraname);
	Camera* GetCamera(GLchar* cameraname);
	void RemoveCamera(GLchar* cameraname);
	void AddTexture(Texture* texture, GLchar* texturename);
	Texture* GetTexture(GLchar* texturename);
	void RemoveTexture(GLchar* texturename);

	//copy constructor and assignment operator diablement
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
};