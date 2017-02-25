#include "Color.hpp"

mgl::Color::Color(float r, float g, float b, float a)
	: m_data {r, g, b, a} {}
mgl::Color::Color(size_t r, size_t g, size_t b, size_t a, size_t MAXIMUM_VALUE)
	: m_data{float(r) / MAXIMUM_VALUE, float(g) / MAXIMUM_VALUE, float(b) / MAXIMUM_VALUE, float(a) / MAXIMUM_VALUE} {}

float mgl::Color::r() { return m_data[0]; }
float mgl::Color::g() { return m_data[1]; }
float mgl::Color::b() { return m_data[2]; }
float mgl::Color::a() { return m_data[3]; }
void  mgl::Color::r(float value) { m_data[0] = value; }
void  mgl::Color::g(float value) { m_data[1] = value; }
void  mgl::Color::b(float value) { m_data[2] = value; }
void  mgl::Color::a(float value) { m_data[3] = value; }
void  mgl::Color::r(size_t value, size_t MAXIMUM_VALUE) { m_data[0] = float(value) / MAXIMUM_VALUE; }
void  mgl::Color::g(size_t value, size_t MAXIMUM_VALUE) { m_data[1] = float(value) / MAXIMUM_VALUE; }
void  mgl::Color::b(size_t value, size_t MAXIMUM_VALUE) { m_data[2] = float(value) / MAXIMUM_VALUE; }
void  mgl::Color::a(size_t value, size_t MAXIMUM_VALUE) { m_data[3] = float(value) / MAXIMUM_VALUE; }