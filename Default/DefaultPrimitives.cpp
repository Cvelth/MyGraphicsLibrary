#include "DefaultPrimitives.hpp"
#include "Primitive\Primitive.hpp"
#include "Math\Vector.hpp"

mgl::Primitive* mgl::changePlacing(Primitive* primitive, PoligonPlacing from, PoligonPlacing to) {
	if (from != PoligonPlacing::zero_Center)
		throw Exceptions::PrimitiveException("Operation currently unsupported.");
	switch (to) {
		case PoligonPlacing::zero_TopLeftCorner:
			*primitive /= mgl::math::Vector(+2.f, +2.f, 1.f, 1.f);
			*primitive += mgl::math::Vector(+.5f, +.5f, 0.f, 0.f);
			break;
		case PoligonPlacing::zero_TopRightCorner:
			*primitive /= mgl::math::Vector(+2.f, +2.f, 1.f, 1.f);
			*primitive += mgl::math::Vector(-.5f, +.5f, 0.f, 0.f);
			break;
		case PoligonPlacing::zero_BottomLeftCorner:
			*primitive /= mgl::math::Vector(+2.f, +2.f, 1.f, 1.f);
			*primitive += mgl::math::Vector(+.5f, -.5f, 0.f, 0.f);
			break;
		case PoligonPlacing::zero_BottomRightCorner:
			*primitive /= mgl::math::Vector(+2.f, +2.f, 1.f, 1.f);
			*primitive += mgl::math::Vector(-.5f, -.5f, 0.f, 0.f);
			break;
		default: break;
	}
	return primitive;
}

mgl::Primitive* mgl::generateN_Polygon(float aspectRatio, size_t n, mgl::Color * color, PoligonPlacing placing, bool isFilled) {
	Primitive* res;
	if (isFilled)
		res = new Primitive(VertexConnectionType::Polygon, color);
	else
		res = new Primitive(VertexConnectionType::LineLoop, color);

	const float PI = 3.14159265359f;
	float STEP = PI / n * 2;
	if (aspectRatio < 1.f && aspectRatio > 0.f)
		for (float f = 0.f; f < PI * 2; f += STEP)
			res->insert(new mgl::math::Vector(aspectRatio * cosf(f), sinf(f)));
	else if (aspectRatio >= 1.f)
		for (float f = 0.f; f < PI * 2; f += STEP)
			res->insert(new mgl::math::Vector(cosf(f), aspectRatio * sinf(f)));
	else
		throw mgl::Exceptions::PrimitiveException("Incorrect input data (aspectRatio).");

	return changePlacing(res, PoligonPlacing::zero_Center, placing);
}

mgl::Primitive* mgl::generateRectangle(float aspectRatio, mgl::Color * color, PoligonPlacing placing, bool isFilled) {
	mgl::Primitive* res;
	if (isFilled)
		res = new Primitive(VertexConnectionType::TriangleStrip, color);
	else
		res = new Primitive(VertexConnectionType::LineLoop, color);
	if (aspectRatio < 1.f && aspectRatio > 0.f) {
		res->insert(new mgl::math::Vector(-aspectRatio, -1.f));
		res->insert(new mgl::math::Vector(+aspectRatio, -1.f));
		res->insert(new mgl::math::Vector(-aspectRatio, +1.f));
		res->insert(new mgl::math::Vector(+aspectRatio, +1.f));
	} else if (aspectRatio >= 1.f) {
		res->insert(new mgl::math::Vector(-1.f, -1.f / aspectRatio));
		res->insert(new mgl::math::Vector(-1.f, +1.f / aspectRatio));
		res->insert(new mgl::math::Vector(+1.f, -1.f / aspectRatio));
		res->insert(new mgl::math::Vector(+1.f, +1.f / aspectRatio));
	} else
		throw mgl::Exceptions::PrimitiveException("Incorrect input data (aspectRatio).");
	return changePlacing(res, PoligonPlacing::zero_Center, placing);
}

mgl::Primitive* mgl::generateCircle(size_t n, mgl::Color * color, PoligonPlacing placing, bool isFilled) {
	return generateN_Polygon(1.f, n, color, placing, isFilled);
}

mgl::Primitive * mgl::generateEllipse(float aspectRatio, size_t n, Color * color, PoligonPlacing placing, bool isFilled) {
	return generateN_Polygon(aspectRatio, n, color, placing, isFilled);
}
