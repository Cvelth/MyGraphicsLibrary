#include "Vertex.hpp"
#include "Math\Vector.hpp"
#include "SharedHeaders\Color.hpp"

mgl::Vertex::Vertex(math::Vector const& coords, Color const& color) {
	m_coords = new mgl::math::Vector(coords);
	m_color = new mgl::Color(color);
}

mgl::Vertex::Vertex(math::Vector && coords, Color && color) {
	m_coords = new mgl::math::Vector(coords);
	m_color = new mgl::Color(color);
}

mgl::Vertex::~Vertex() {
	if (m_coords) delete m_coords;
	if (m_color) delete m_color;
}

void mgl::Vertex::set(math::Vector const& coords, Color const& color) {
	if (m_coords) delete m_coords;
	m_coords = new mgl::math::Vector(coords);
	if (m_color) delete m_color;
	m_color = new mgl::Color(color);
}

void mgl::Vertex::set(math::Vector && coords, Color && color) {
	if (m_coords) delete m_coords;
	m_coords = new mgl::math::Vector(coords);
	if (m_color) delete m_color;
	m_color = new mgl::Color(color);
}