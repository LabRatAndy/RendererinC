#include "Attribute.h"

Attribute::Attribute(const GLchar * Name, const GLuint Index, const GLint Size, const GLint Stride, const GLint Offset, GLenum Type,GLenum Normalised)
{
	name = Name;
	index = Index;
	size = Size;
	stride = Stride;
	offset = Offset;
	type = Type;
	normalised = Normalised;
}

void Attribute::SetAttribute()
{
	glVertexAttribPointer(index, size, type, normalised, stride, (void*)offset);
}

void Attribute::EnableAttribute()
{
	glEnableVertexAttribArray(index);
}

void Attribute::DisableAttribute()
{
	glDisableVertexAttribArray(index);
}
