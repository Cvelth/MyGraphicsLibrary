#include "Vertex.hpp"
#include "Math\Vector.hpp"
#include "OpenGL_Mirror\BasicTypes\Color.hpp"

mgl::Vertex::Vertex(math::Vector * coords, Color * color) : m_coords(coords), m_color(color) {}

mgl::Vertex::~Vertex() {
	if (m_coords) delete m_coords;
	if (m_color) delete m_color;
}

void mgl::Vertex::set(math::Vector * coords, Color * color) {
	if (m_coords) delete m_coords;
	m_coords = coords;
	if (m_color) delete m_color;
	m_color = color;
}