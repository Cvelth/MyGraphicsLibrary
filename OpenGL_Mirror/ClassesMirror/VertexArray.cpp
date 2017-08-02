#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "VertexArray.hpp"

mgl::VertexArray::VertexArray() {
	glCreateVertexArrays(1, &m_id);
}

mgl::VertexArray::VertexArray(unsigned int id)
	: m_id(id) {}

mgl::VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_id);
}

unsigned int mgl::VertexArray::id() const {
	return m_id;
}

void mgl::VertexArray::bind() {
	glBindVertexArray(m_id);
}

void mgl::VertexArray::enableAttrib(unsigned int index) {
	glEnableVertexAttribArray(index);
}

void mgl::VertexArray::attribPointer(const char* fieldName, size_t size,
									 bool normalized, size_t stride, size_t shift) {
	//glVertexAttribPointer(loc, (GLint) size, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE,
	//					  sizeof(float) * (GLsizei) stride, (const void*) (sizeof(float) * shift));
}