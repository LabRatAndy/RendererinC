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

bool ResourceManager::AddCamera(Camera * camera, GLchar * cameraname)
{
	if (camera == nullptr) return false;
	if (cameraname == nullptr) return false;
	if (strlen(cameraname) == 0) return false;
	if (strcmp(cameraname, " ")) return false;
	cameraDictionary.insert(std::pair<GLchar*, Camera*>(cameraname, camera));
	return true;
}

Camera * ResourceManager::GetCamera(GLchar * cameraname)
{
#ifdef DEBUG
	try
	{
#endif
		return cameraDictionary.at(cameraname);
#ifdef DEBUG
	}
	catch (std::out_of_range e)
	{
		return nullptr;
	}
#endif
}

void ResourceManager::RemoveCamera(GLchar * cameraname)
{
	cameraDictionary.erase(cameraname);
}

bool ResourceManager::AddTexture(Texture * texture, GLchar * texturename)
{
	if (texture == nullptr) return false;
	if (texturename == nullptr) return false;
	if (strlen(texturename) == 0) return false;
	if (strcmp(texturename, " ")) return false;
	textureDictionary.insert(std::pair<GLchar*, Texture*>(texturename, texture));
	return true;
}

Texture * ResourceManager::GetTexture(GLchar * texturename)
{
#ifdef DEBUG
	try
	{
#endif
		return textureDictionary.at(texturename);
#ifdef DEBUG
	}
	catch (std::out_of_range e)
	{
		return nullptr;
	}
#endif
}

void ResourceManager::RemoveTexture(GLchar * texturename)
{
	textureDictionary.erase(texturename);
}
