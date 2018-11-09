#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	//TODO clean up any  remaining resoruces
}
ResourceManager & ResourceManager::Instance(void)
{
	static ResourceManager instance;
	return instance;
}

bool ResourceManager::AddShader(Shader * shader, GLchar * shadername)
{
	// return false not worked if shader is null shadername is null / zero length/ contains only a space
	if (shader == nullptr) return false;
	if (shadername == nullptr)return false;
	if (strlen(shadername) == 0) return false;
	if (strcmp(shadername, " ")) return false;
	// passed all checks now add to the map
	shaderDictionary.insert(std::pair<GLchar*, Shader*>(shadername, shader));
	return true;
}

Shader * ResourceManager::GetShader(GLchar * shadername)
{
#ifdef DEBUG
	try
	{
#endif
		return shaderDictionary.at(shadername);
#ifdef DEBUG
	}
	catch  (std::out_of_range e)
	{
		return nullptr;
	}
#endif
}

void ResourceManager::RemoveShader(GLchar * shadername)
{
	shaderDictionary.erase(shadername);
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
