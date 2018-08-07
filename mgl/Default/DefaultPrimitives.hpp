#pragma once
#include "../MyGraphicsLibrary/MGL/Default/DefaultColors.hpp"

namespace mgl {
	class Primitive;

	enum class PoligonPlacing {
		zero_in_center, 
		zero_in_top_left, zero_in_top_right, 
		zero_in_bottom_left, zero_in_bottom_right
	};
	Primitive* changePlacing(Primitive* primitive, PoligonPlacing from, PoligonPlacing to);

	Primitive* generateN_Polygon(float aspectRatio = 1.f, size_t n = 6, Color* color = Colors::Black(), PoligonPlacing placing = PoligonPlacing::zero_in_center, bool isFilled = false);
	Primitive* generateRectangle(float aspectRatio = 1.f, Color* color = Colors::Black(), PoligonPlacing placing = PoligonPlacing::zero_in_center, bool isFilled = false);
	Primitive* generateCircle(size_t n = 60, Color* color = Colors::Black(), PoligonPlacing placing = PoligonPlacing::zero_in_center, bool isFilled = false);
	Primitive* generateEllipse(float aspectRatio = 1.f, size_t n = 60, Color* color = Colors::Black(), PoligonPlacing placing = PoligonPlacing::zero_in_center, bool isFilled = false);
}