#include "../MyGraphicsLibrary/MGL/OpenGL/OpenGL_Dependency/OpenGL.h"
#include "VertexArray.hpp"

mgl::VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_id);
}

mgl::VertexArray::VertexArray(unsigned int id) {
	if (glIsVertexArray(id))
		m_id = id;
	else
		throw Exceptions::VertexArrayException("Invalid ID was passed.");
}

mgl::VertexArray::VertexArray(const VertexArray & vao) : VertexArray(vao.m_id) {}

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
void mgl::VertexArray::initializeAttribPointer(ShaderVariable const& attrib, size_t size,
											   bool normalized, size_t stride, size_t shift) {
	if (attrib.variable_type != mgl::ShaderVariableType::Attribute)
		throw Exceptions::VertexArrayException("Non-atribute variale was passed.");
	glVertexAttribPointer(attrib.location, (GLint) size, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE,
						  sizeof(float) * (GLsizei) stride, (const void*) (sizeof(float) * shift));
	glEnableVertexAttribArray(attrib.location);
	m_data.insert(AttributePointerDataType(&attrib, VertexShaderAttributePointerData(size, normalized, stride, shift)));
}
void mgl::VertexArray::repeatAttribPointer(ShaderVariable const& attrib) {
	auto t = m_data.at(&attrib);
	glVertexAttribPointer(attrib.location, (GLint) t.size, GL_FLOAT, t.normalized ? GL_TRUE : GL_FALSE,
						  sizeof(float) * (GLsizei) t.stride, (const void*) (sizeof(float) * t.shift));
}

void mgl::VertexArray::repeatAllAttribPointers() {
	for (auto it : m_data) 
		glVertexAttribPointer(it.first->location, (GLint) it.second.size, GL_FLOAT, it.second.normalized ? GL_TRUE : GL_FALSE,
							  sizeof(float) * (GLsizei) it.second.stride, (const void*) (sizeof(float) * it.second.shift));
}