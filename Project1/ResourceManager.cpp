#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
}
ResourceManager & ResourceManager::Instance(void)
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::AddShader(Shader * shader, GLchar * shadername)
{
}

Shader * ResourceManager::GetShader(GLchar * shadername)
{
	return nullptr;
}

void ResourceManager::RemoveShader(GLchar * shadername)
{
}

void ResourceManager::AddCamera(Camera * camera, GLchar * cameraname)
{
}

Camera * ResourceManager::GetCamera(GLchar * cameraname)
{
	return nullptr;
}

void ResourceManager::RemoveCamera(GLchar * cameraname)
{
}

void ResourceManager::AddTexture(Texture * texture, GLchar * texturename)
{
}

Texture * ResourceManager::GetTexture(GLchar * texturename)
{
	return nullptr;
}

void ResourceManager::RemoveTexture(GLchar * texturename)
{
}
