#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "Primitive.hpp"
#include "Math\Vector.hpp"
#include "OpenGL_Mirror\BasicTypes\Buffer.hpp"
#include "OpenGL_Mirror\BasicTypes\Color.hpp"
#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"


mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type) {
	m_buffer = new Buffer();
	m_connection = type;
	m_basic_color = basicColor;
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, const float* array, size_t size, size_t COORDS_POINT_NUMBER, size_t COLOR_POINT_NUMBER) : Primitive(basicColor, type) {
	if (size % COORDS_POINT_NUMBER + COLOR_POINT_NUMBER != 0)
		throw Exceptions::PrimitiveException("Wrong elements number.");

	COORDS_POINT_NUMBER--; COLOR_POINT_NUMBER--;
	for (size_t i = 0; i < size; i += COORDS_POINT_NUMBER + COLOR_POINT_NUMBER)
		m_data.push_back(Vertex(new mgl::math::Vector(COORDS_POINT_NUMBER >= 0 ? array[i + 0] : 0,
													  COORDS_POINT_NUMBER >= 1 ? array[i + 1] : 0,
													  COORDS_POINT_NUMBER >= 2 ? array[i + 2] : 0,
													  COORDS_POINT_NUMBER >= 3 ? array[i + 3] : 0),

								new mgl::Color(COLOR_POINT_NUMBER >= 0 ? array[i + COORDS_POINT_NUMBER + 0] : 0,
											   COLOR_POINT_NUMBER >= 1 ? array[i + COORDS_POINT_NUMBER + 1] : 0,
											   COLOR_POINT_NUMBER >= 2 ? array[i + COORDS_POINT_NUMBER + 2] : 0,
											   COLOR_POINT_NUMBER >= 3 ? array[i + COORDS_POINT_NUMBER + 3] : 0))
								);
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, math::Vector* coords_array, size_t size) : Primitive(basicColor, type) {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(Vertex(&coords_array[i], m_basic_color));
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, math::Vector* coords_array, Color* colors_array, size_t size) : Primitive(basicColor, type) {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(Vertex(&coords_array[i], &colors_array[i]));
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, const std::initializer_list<math::Vector*>& coords_list) : Primitive(basicColor, type) {
	for (auto it : coords_list)
		m_data.push_back(Vertex(it, m_basic_color));
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, const std::initializer_list<math::Vector*>& coords_list, const std::initializer_list<Color*>& color_list) : Primitive(basicColor, type) {
	auto it1 = coords_list.begin(); 
	auto it2 = color_list.begin();
	for (; it1 != coords_list.end() || it2 != color_list.end(); it1++, it2++)
		m_data.push_back(Vertex(*it1, *it2));
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, const std::list<math::Vector*>& coords_list) : Primitive(basicColor, type) {
	for (auto it : coords_list)
		m_data.push_back(Vertex(it, m_basic_color));
}
mgl::Primitive::Primitive(Color* basicColor, VertexConnectionType type, const std::list<math::Vector*>& coords_list, const std::list<Color*>& color_list) : Primitive(basicColor, type) {
	auto it1 = coords_list.begin();
	auto it2 = color_list.begin();
	for (; it1 != coords_list.end() || it2 != color_list.end(); it1++, it2++)
		m_data.push_back(Vertex(*it1, *it2));
}

mgl::Primitive::~Primitive() {
	delete m_buffer;
	delete m_basic_color;
}

size_t mgl::Primitive::getSize() const {
	return m_data.size() * 8;
}

size_t mgl::Primitive::getNumber() const {
	return m_data.size();
}

void mgl::Primitive::insert(math::Vector* v) {
	m_data.push_back(Vertex(v, m_basic_color));
}

void mgl::Primitive::insert(math::Vector * v, Color * c) {
	m_data.push_back(Vertex(v, c));
}

void mgl::Primitive::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto it : m_data) {
		temp[i++] = it.coords()->x();
		temp[i++] = it.coords()->y();
		temp[i++] = it.coords()->z();
		temp[i++] = it.coords()->w();

		temp[i++] = it.color()->r();
		temp[i++] = it.color()->g();
		temp[i++] = it.color()->b();
		temp[i++] = it.color()->a();
	}
	m_buffer->bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * getSize(), temp, _enumSwitch(u));
	delete[] temp;
}

void mgl::Primitive::draw() { 
	m_buffer->bind();
	glDrawArrays(_enumSwitch(m_connection), 0, (GLsizei)getSize()); 
}

std::list<mgl::Vertex>& mgl::Primitive::operator*() {
	return m_data;
}

const std::list<mgl::Vertex>& mgl::Primitive::operator*() const {
	return m_data;
}

mgl::Vertex::Vertex(math::Vector * coords, Color * color) : m_coords(coords), m_color(color) {}

mgl::Vertex::~Vertex() {
	delete m_coords; 
	delete m_color; 
}

void mgl::Vertex::set(math::Vector * coords, Color * color) {
	if (m_coords) delete m_coords;
	m_coords = coords;
	if (m_color) delete m_color;
	m_color = color;
}
