#include "EBO.h"

ElementBufferObject::ElementBufferObject(GLint * ibo,GLint size)
{
	glGenBuffers(1, &handle);
	this->ibo = ibo;
	count = size;
}

ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &handle);
	if (ibo != nullptr) delete ibo;
}

void ElementBufferObject::Bind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
}

void ElementBufferObject::BufferData(GLenum drawtype)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(GLint), ibo, drawtype);
}

void ElementBufferObject::Draw(void)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void ElementBufferObject::Unbind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
