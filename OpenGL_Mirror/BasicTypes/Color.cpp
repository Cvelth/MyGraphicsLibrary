#include "Color.hpp"

mgl::Color::Color(float r, float g, float b, float a) { 
	set(r, g, b, a); 
}
mgl::Color::Color(size_t r, size_t g, size_t b, size_t a, size_t MAXIMUM_VALUE) {
	set(float(r) / MAXIMUM_VALUE, float(g) / MAXIMUM_VALUE, float(b) / MAXIMUM_VALUE, float(a) / MAXIMUM_VALUE);
}

float mgl::Color::r() const { return x(); }
float mgl::Color::g() const { return y(); }
float mgl::Color::b() const { return z(); }
float mgl::Color::a() const { return w(); }
void  mgl::Color::r(float value) { x(value); }
void  mgl::Color::g(float value) { y(value); }
void  mgl::Color::b(float value) { z(value); }
void  mgl::Color::a(float value) { w(value); }
void  mgl::Color::r(size_t value, size_t MAXIMUM_VALUE) { x(float(value) / MAXIMUM_VALUE); }
void  mgl::Color::g(size_t value, size_t MAXIMUM_VALUE) { y(float(value) / MAXIMUM_VALUE); }
void  mgl::Color::b(size_t value, size_t MAXIMUM_VALUE) { z(float(value) / MAXIMUM_VALUE); }
void  mgl::Color::a(size_t value, size_t MAXIMUM_VALUE) { w(float(value) / MAXIMUM_VALUE); }