#include "EBO.h"

ElementBufferObject::ElementBufferObject(GLint * ibo)
{
	glGenBuffers(1, &handle);
	this->ibo = ibo;
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo), ibo, drawtype);
	delete ibo;
	ibo = nullptr;
}

void ElementBufferObject::Unbind(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
