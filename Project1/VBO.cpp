#include"VBO.h"

VertexBufferObject::VertexBufferObject(GLfloat *vertices, GLint size)
{
	glGenBuffers(1, &handle);
	vertexData = vertices;
	dataSize = size;
}

void VertexBufferObject::Bind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
}

void VertexBufferObject::BufferData(GLenum DrawType)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, dataSize*sizeof(GLfloat), vertexData, DrawType);
}

void VertexBufferObject::Draw(GLint first, GLint count)
{
	glDrawArrays(GL_TRIANGLES, first, count);
}

void VertexBufferObject::UnBind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &handle);
	if(vertexData != nullptr) delete vertexData;
}
