#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "VertexArray.hpp"

mgl::VertexArray::VertexArray() {
	glCreateVertexArrays(1, &m_id);
}

mgl::VertexArray::VertexArray(unsigned int id) {
	if (glIsVertexArray(id))
		m_id = id;
	else
		throw Exceptions::VertexArrayException("Invalid ID was passed.");
}

mgl::VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_id);
}

bool mgl::VertexArray::isValid() {
	return glIsVertexArray(m_id);
}

unsigned int mgl::VertexArray::id() const {
	return m_id;
}

void mgl::VertexArray::bind() {
	glBindVertexArray(m_id);
}

#include "ShaderVariable.hpp"
void mgl::VertexArray::attribPointer(const ShaderVariable& attrib, size_t size,
									 bool normalized, size_t stride, size_t shift) {
	if (attrib.variable_type != mgl::ShaderVariableType::Attribute)
		throw Exceptions::VertexArrayException("Non-atribute variale was passed.");
	glVertexAttribPointer(attrib.location, (GLint) size, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE,
						  sizeof(float) * (GLsizei) stride, (const void*) (sizeof(float) * shift));
	glEnableVertexAttribArray(attrib.location);
}