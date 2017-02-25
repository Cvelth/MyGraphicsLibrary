#include "OpenGL_header.h"
#include "Buffer.hpp"

mgl::BufferArray::BufferArray(unsigned int n) : size(n) {
	m_id = new unsigned int[size];
	glGenBuffers(size, m_id);
}

mgl::BufferArray::~BufferArray() {
	glDeleteBuffers(size, m_id);
	delete[] m_id;
}

unsigned int mgl::BufferArray::id(unsigned int n) const {
	if (n > size)
		throw BufferException("There are no such buffer generated");
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
