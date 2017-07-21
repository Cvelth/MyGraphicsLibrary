#pragma once
#include "Primitive.hpp"

namespace mgl {
	Primitive generateN_Polygon(size_t n = 6);
	Primitive generateRectangle(float aspectRatio = 1.f);
	Primitive generateCircle(size_t n = 60);
}