#include "Vertex.hpp"
#include "../MyGraphicsLibrary/MGL/Math/Vector.hpp"
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Color.hpp"

mgl::Vertex::Vertex(math::vectorH const& coords, Color const& color) {
	m_coords = new mgl::math::vectorH(coords);
	m_color = new mgl::Color(color);
}

mgl::Vertex::Vertex(math::vectorH && coords, Color && color) {
	m_coords = new mgl::math::vectorH(coords);
	m_color = new mgl::Color(color);
}

mgl::Vertex::~Vertex() {
	if (m_coords) delete m_coords;
	if (m_color) delete m_color;
}

void mgl::Vertex::set(math::vectorH const& coords, Color const& color) {
	if (m_coords) delete m_coords;
	m_coords = new mgl::math::vectorH(coords);
	if (m_color) delete m_color;
	m_color = new mgl::Color(color);
}

void mgl::Vertex::set(math::vectorH && coords, Color && color) {
	if (m_coords) delete m_coords;
	m_coords = new mgl::math::vectorH(coords);
	if (m_color) delete m_color;
	m_color = new mgl::Color(color);
}