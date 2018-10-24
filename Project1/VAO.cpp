#include "VAO.h"

VertexArrayObject::VertexArrayObject(GLint numberofattribs)
{
	maxattributes = numberofattribs;
	glGenVertexArrays(1, &handle);
	attributelist = new Attribute[maxattributes];
}

void VertexArrayObject::AddAttribute(GLint index, Attribute attribute)
{
	if (index >= maxattributes)return;
	if (index < 0) return;
	attributelist[index] = attribute;
}

void VertexArrayObject::SetVBO(VertexBufferObject * VBO)
{
	if (vbo == nullptr)vbo = VBO;
	else
	{
		vbo->UnBind();
		delete vbo;
		vbo = VBO;
	}
	vbo->Bind();
}

void VertexArrayObject::SetIBO(ElementBufferObject * IBO)
{
	if (ibo == nullptr)ibo = IBO;
	else
	{
		ibo->Unbind();
		delete ibo;
		ibo = IBO;
	}
	ibo->Bind();
}

void VertexArrayObject::Bind(void)
{
	glBindVertexArray(handle);
}

void VertexArrayObject::Unbind(void)
{
	glBindVertexArray(0);
}

void VertexArrayObject::SetAttributes(void)
{
	for (int n = 0; n < maxattributes; n++)
	{
		attributelist[n].SetAttribute();
		attributelist[n].EnableAttribute();
	}
}

void VertexArrayObject::Draw(void)
{
	ibo->Draw();
}

void VertexArrayObject::Draw(GLint first, GLint count)
{
	vbo->Draw(first, count);
}

VertexArrayObject::~VertexArrayObject()
{
	delete attributelist;
	delete vbo;
	delete ibo;
	glDeleteVertexArrays(1, &handle);
}
