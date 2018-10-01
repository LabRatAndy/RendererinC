#include"Texture.h"

Texture::Texture(const GLchar * texturefilename)
{
	Cubemapped = false;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	int width, height;
	unsigned char* texture = SOIL_load_image(texturefilename, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::Texture(const GLchar* top, const GLchar* bottom, const GLchar* left, const GLchar* right, const GLchar* front, const GLchar* back)
{
	Cubemapped = true;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	GLint width, height;
	unsigned char* texture = SOIL_load_image(top, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	SOIL_free_image_data(texture);
	texture = SOIL_load_image(bottom, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	SOIL_free_image_data(texture);
	texture = SOIL_load_image(left, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	SOIL_free_image_data(texture);
	texture = SOIL_load_image(right, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	SOIL_free_image_data(texture);
	texture = SOIL_load_image(front, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	SOIL_free_image_data(texture);
	texture = SOIL_load_image(back, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	SOIL_free_image_data(texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}
Texture::~Texture()
{
	glDeleteTextures(1, &handle);
}

void Texture::Bind()
{
	if (Cubemapped)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, handle);
	}
}

void Texture::Unbind()
{
	if (Cubemapped)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Texture::Activate(GLenum textureunit)
{
	glActiveTexture(textureunit);
}

GLboolean Texture::IsCubeMapped()
{
	return Cubemapped;
}

void Texture::SetTexParameterI(GLenum parametername, GLint parameter)
{
	if (Cubemapped)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, parametername, parameter);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, handle);
		glTexParameteri(GL_TEXTURE_2D, parametername, parameter);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
