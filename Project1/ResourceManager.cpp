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
