#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "Primitive.hpp"
#include "Math\Vector.hpp"
#include "OpenGL_Mirror\BasicTypes\Buffer.hpp"
#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"

mgl::Primitive::Primitive(VertexConnectionType type) {
	m_buffer = new Buffer();
	m_connection = type;
}

mgl::Primitive::Primitive(VertexConnectionType type, const float* array, size_t size, size_t POINTS_NUMBER) : Primitive(type) {
	if (size % POINTS_NUMBER != 0)
		throw Exceptions::PrimitiveException("Wrong elements number.");
	for (size_t i = 0; i < size; i += POINTS_NUMBER)
		m_data.push_back(new Vector(POINTS_NUMBER >= 0 ? array[i + 0] : 0,
								POINTS_NUMBER >= 1 ? array[i + 1] : 0,
								POINTS_NUMBER >= 2 ? array[i + 2] : 0,
								POINTS_NUMBER >= 3 ? array[i + 3] : 0));
}

mgl::Primitive::Primitive(VertexConnectionType type, Vector * array, size_t size) : Primitive(type) {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(&array[i]);
}

mgl::Primitive::Primitive(VertexConnectionType type, const std::initializer_list<Vector*>& list) : Primitive(type) {
	for (auto it : list)
		m_data.push_back(it);
}

mgl::Primitive::Primitive(VertexConnectionType type, const std::list<Vector*>& list) : Primitive(type) {
	for (auto it : list)
		m_data.push_back(it);
}

mgl::Primitive::~Primitive() {
	//delete m_buffer;
}

size_t mgl::Primitive::getSize() const {
	return m_data.size() * 4;
}

size_t mgl::Primitive::getNumber() const {
	return m_data.size();
}

void mgl::Primitive::insert(Vector* v) {
	m_data.push_back(v);
}

void mgl::Primitive::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto v : m_data) {
		temp[i++] = v->x();
		temp[i++] = v->y();
		temp[i++] = v->z();
		temp[i++] = v->w();
	}
	m_buffer->bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * getSize(), temp, _enumSwitch(u));
	delete[] temp;
}

void mgl::Primitive::bind() {
	m_buffer->bind();
}

void mgl::Primitive::draw() { 
	m_buffer->bind();
	glDrawArrays(_enumSwitch(m_connection), 0, (GLsizei)getSize()); 
}

std::list<mgl::Vector*>& mgl::Primitive::operator*() {
	return m_data;
}

const std::list<mgl::Vector*>& mgl::Primitive::operator*() const {
	return m_data;
}
///////////////////////////////////////////////////////////
mgl::PrimitiveSet::PrimitiveSet() {
}

mgl::PrimitiveSet::PrimitiveSet(const Primitive * array, size_t size) {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(array[i]);
}

mgl::PrimitiveSet::PrimitiveSet(const std::initializer_list<Primitive>& list) {
	for (auto it : list)
		m_data.push_back(it);
}

mgl::PrimitiveSet::PrimitiveSet(const std::list<Primitive>& list) {
	for (auto it : list)
		m_data.push_back(it);
}

size_t mgl::PrimitiveSet::getSize() const {
	size_t res = 0;
	for (auto it : m_data)
		res += it.getSize();
	return res;
}

size_t mgl::PrimitiveSet::getNumber() const {
	size_t res = 0;
	for (auto it : m_data)
		res += it.getNumber();
	return res;
}

void mgl::PrimitiveSet::insert(const Primitive & v) {
	m_data.push_back(v);
}

void mgl::PrimitiveSet::send(DataUsage u) {
	for (auto it : m_data)
		it.send(u);
}

std::list<mgl::Primitive>& mgl::PrimitiveSet::operator*() {
	return m_data;
}

const std::list<mgl::Primitive>& mgl::PrimitiveSet::operator*() const {
	return m_data;
}