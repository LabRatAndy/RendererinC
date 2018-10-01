#include"VBO.h"

VertexBufferObject::VertexBufferObject(GLfloat * vertices)
{
	glGenBuffers(1, &handle);
	vertexData = vertices;
}

void VertexBufferObject::Bind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VertexBufferObject::BufferData(GLenum DrawType)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, DrawType);
	delete vertexData;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::UnBind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &handle);
	delete vertexData;
}
