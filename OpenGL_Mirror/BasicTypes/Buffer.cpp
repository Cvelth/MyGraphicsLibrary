#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "Buffer.hpp"

mgl::BufferArray::BufferArray(unsigned int n) : m_size(n) {
	m_id = new unsigned int[m_size];
	glGenBuffers(m_size, m_id);
}

mgl::BufferArray::~BufferArray() {
	glDeleteBuffers(m_size, m_id);
	delete[] m_id;
}

unsigned int mgl::BufferArray::id(unsigned int n) const {
	if (n > m_size)
		throw BufferException("The index is out of array bounds");
	return m_id[n];
}

mgl::Buffer mgl::BufferArray::operator[](unsigned int n) {
	return Buffer(id(n));
}

mgl::Buffer::Buffer() {
	glGenBuffers(1, &m_id);
}

mgl::Buffer::Buffer(unsigned int id) 
	: m_id(id) {
}

mgl::Buffer::~Buffer() {
	glDeleteBuffers(1, &m_id);
}

unsigned int mgl::Buffer::id() const {
	return m_id;
}

void mgl::Buffer::bind(BufferBindingPoint p) {
	glBindBuffer(switchEnum(p), m_id);
}
