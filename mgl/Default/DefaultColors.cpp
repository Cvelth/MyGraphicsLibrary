#include "DefaultColors.hpp"
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Color.hpp"

mgl::Color* mgl::Colors::Black() {
	return new mgl::Color(0.f, 0.f, 0.f, 1.f);
}
mgl::Color* mgl::Colors::White() {
	return new mgl::Color(1.f, 1.f, 1.f, 1.f);
}
mgl::Color* mgl::Colors::Red() {
	return new mgl::Color(1.f, 0.f, 0.f, 1.f);
}
mgl::Color* mgl::Colors::Green() {
	return new mgl::Color(0.f, 1.f, 0.f, 1.f);
}
mgl::Color* mgl::Colors::Blue() {
	return new mgl::Color(0.f, 0.f, 1.f, 1.f);
}

mgl::Color * mgl::Colors::Grey(float i) {
	return new mgl::Color(i, i, i, 1.f);
}
