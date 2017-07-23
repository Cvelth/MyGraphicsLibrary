#pragma once
#include "OpenGL_Mirror\BasicTypes\BasicColors.hpp"

namespace mgl {
	class Primitive;

	Primitive* generateN_Polygon(size_t n = 6, Color* color = Colors::Black(), bool isFilled = false);
	Primitive* generateRectangle(float aspectRatio = 1.f, Color* color = Colors::Black(), bool isFilled = false);
	Primitive* generateCircle(size_t n = 60, Color* color = Colors::Black(), bool isFilled = false);
}