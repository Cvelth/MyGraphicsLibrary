#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "Primitive.hpp"
#include "Math\Vector.hpp"
#include "OpenGL_Mirror\ClassesMirror\Buffer.hpp"
#include "SharedHeaders\Color.hpp"
#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"
#include "Vertex.hpp"

mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor) : AbstractSendableArray() {
	if (defaultColor == nullptr)
		defaultColor = new mgl::Color();

	m_connection = type;
	m_default_color = defaultColor;
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, const float* array, size_t size, size_t COORDS_POINT_NUMBER, size_t COLOR_POINT_NUMBER) : Primitive(type, defaultColor) {
	if (size % COORDS_POINT_NUMBER + COLOR_POINT_NUMBER != 0)
		throw Exceptions::PrimitiveException("Wrong elements number.");

	COORDS_POINT_NUMBER--; COLOR_POINT_NUMBER--;
	for (size_t i = 0; i < size; i += COORDS_POINT_NUMBER + COLOR_POINT_NUMBER)
		m_data.push_back(new Vertex(new mgl::math::Vector(COORDS_POINT_NUMBER >= 0 ? array[i + 0] : 0,
													  COORDS_POINT_NUMBER >= 1 ? array[i + 1] : 0,
													  COORDS_POINT_NUMBER >= 2 ? array[i + 2] : 0,
													  COORDS_POINT_NUMBER >= 3 ? array[i + 3] : 0),
									new mgl::Color(COLOR_POINT_NUMBER >= 0 ? array[i + COORDS_POINT_NUMBER + 0] : 0,
												   COLOR_POINT_NUMBER >= 1 ? array[i + COORDS_POINT_NUMBER + 1] : 0,
												   COLOR_POINT_NUMBER >= 2 ? array[i + COORDS_POINT_NUMBER + 2] : 0,
												   COLOR_POINT_NUMBER >= 3 ? array[i + COORDS_POINT_NUMBER + 3] : 0))
									);
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, math::Vector* coords_array, size_t size) : Primitive(type, defaultColor) {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(new Vertex(&coords_array[i], m_default_color));
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, math::Vector* coords_array, Color* colors_array, size_t size) : Primitive(type, defaultColor) {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(new Vertex(&coords_array[i], &colors_array[i]));
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, const std::initializer_list<math::Vector*>& coords_list) : Primitive(type, defaultColor) {
	for (auto it : coords_list)
		m_data.push_back(new Vertex(it, m_default_color));
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, const std::initializer_list<math::Vector*>& coords_list, const std::initializer_list<Color*>& color_list) : Primitive(type, defaultColor) {
	auto it1 = coords_list.begin(); 
	auto it2 = color_list.begin();
	for (; it1 != coords_list.end() || it2 != color_list.end(); it1++, it2++)
		m_data.push_back(new Vertex(*it1, *it2));
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, const std::list<math::Vector*>& coords_list) : Primitive(type, defaultColor) {
	for (auto it : coords_list)
		m_data.push_back(new Vertex(it, m_default_color));
}
mgl::Primitive::Primitive(VertexConnectionType type, Color* defaultColor, const std::list<math::Vector*>& coords_list, const std::list<Color*>& color_list) : Primitive(type, defaultColor) {
	auto it1 = coords_list.begin();
	auto it2 = color_list.begin();
	for (; it1 != coords_list.end() || it2 != color_list.end(); it1++, it2++)
		m_data.push_back(new Vertex(*it1, *it2));
}

mgl::Primitive::~Primitive() {
	for (auto it : m_data)
		delete it;
	delete m_default_color;
}

size_t mgl::Primitive::getSize() const {
	return m_data.size() * 8;
}

size_t mgl::Primitive::getNumber() const {
	return m_data.size();
}

mgl::Color* mgl::Primitive::getDefaultColor() const {
	return m_default_color;
}

void mgl::Primitive::setDefaultColor(Color* color) {
	if (color == nullptr)
		throw Exceptions::PrimitiveException("Null color was inserted");
	m_default_color = color;
}

void mgl::Primitive::setDefaultColor(float r, float g, float b, float a) {
	setDefaultColor(new mgl::Color(r, g, b, a));
}

void mgl::Primitive::insert(math::Vector* v) {
	insert(new mgl::Vertex(v, m_default_color));
}

void mgl::Primitive::insert(math::Vector * v, Color * c) {
	insert(new Vertex(v, c));
}

void mgl::Primitive::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto it : m_data) {
		temp[i++] = it->coords()->x();
		temp[i++] = it->coords()->y();
		temp[i++] = it->coords()->z();
		temp[i++] = it->coords()->w();
					
		temp[i++] = it->color()->r();
		temp[i++] = it->color()->g();
		temp[i++] = it->color()->b();
		temp[i++] = it->color()->a();
	}
	buffer_data(getSize(), temp, u);
	delete[] temp;
}

void mgl::Primitive::draw() { 
	if (!wasBufferGenerated())
		throw Exceptions::PrimitiveException("Data wasn't sent");
	buffer_bind();
	glDrawArrays(switchEnum(m_connection), 0, (GLsizei) getNumber());
}

std::list<mgl::Vertex*>& mgl::Primitive::operator*() {
	return m_data;
}

const std::list<mgl::Vertex*>& mgl::Primitive::operator*() const {
	return m_data;
}

const mgl::Primitive & mgl::Primitive::operator+=(const mgl::math::Vector& v) {
	for (auto it : m_data)
		*it->coords() += v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator+=(mgl::math::Vector && v) {
	for (auto it : m_data)
		*it->coords() += v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator+=(mgl::math::Vector * v) {
	for (auto it : m_data)
		*it->coords() += *v;
	return *this;
}

const mgl::Primitive & mgl::Primitive::operator-=(const mgl::math::Vector& v) {
	for (auto it : m_data)
		*it->coords() -= v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator-=(mgl::math::Vector && v) {
	for (auto it : m_data)
		*it->coords() -= v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator-=(mgl::math::Vector * v) {
	for (auto it : m_data)
		*it->coords() -= *v;
	return *this;
}

const mgl::Primitive & mgl::Primitive::operator*=(const mgl::math::Vector& v) {
	for (auto it : m_data)
		*it->coords() *= v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator*=(mgl::math::Vector&& v) {
	for (auto it : m_data)
		*it->coords() *= v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator*=(mgl::math::Vector* v) {
	for (auto it : m_data)
		*it->coords() *= *v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator/=(const mgl::math::Vector& v) {
	for (auto it : m_data)
		*it->coords() /= v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator/=(mgl::math::Vector&& v) {
	for (auto it : m_data)
		*it->coords() /= v;
	return *this;
}
const mgl::Primitive & mgl::Primitive::operator/=(mgl::math::Vector* v) {
	for (auto it : m_data)
		*it->coords() /= *v;
	return *this;
}

const mgl::Primitive & mgl::Primitive::operator*=(const float f) {
	for (auto it : m_data)
		*it->coords() *= f;
	return *this;
}

const mgl::Primitive & mgl::Primitive::operator/=(const float f) {
	for (auto it : m_data)
		*it->coords() /= f;
	return *this;
}